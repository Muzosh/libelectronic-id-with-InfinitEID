#include "CustomJavaCard.hpp"

#include "pcsc-common.hpp"

using namespace pcsc_cpp;

namespace
{

const byte_vector SELECT_MAIN_AID {0x00, 0xA4, 0x04, 0x00, 0x08, 0x01, 0x02,
                                   0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

const byte_vector SELECT_MASTER_FILE {0x00, 0xA4, 0x00, 0x0C, 0x00};

const std::vector<byte_vector> SELECT_AUTH_CERT_FILE = {
    SELECT_MAIN_AID,
    {0x00, 0xA4, 0x02, 0x0C, 0x02, 0xAA, 0xCE},
};
const std::vector<byte_vector> SELECT_SIGN_CERT_FILE = {
    SELECT_MAIN_AID,
    {0x00, 0xA4, 0x02, 0x0C, 0x02, 0xDD, 0xCE},
};

// const byte_vector::value_type AUTH_PIN_REFERENCE = 0x01;
// const byte_vector::value_type SIGNING_PIN_REFERENCE = 0x02;

} // namespace

namespace electronic_id
{

byte_vector CustomJavaCard::getCertificateImpl(const CertificateType type) const
{
    return electronic_id::getCertificate(
        *card, type.isAuthentication() ? SELECT_AUTH_CERT_FILE : SELECT_SIGN_CERT_FILE);
}

byte_vector CustomJavaCard::signWithAuthKeyImpl(const byte_vector& pin,
                                                const byte_vector& hash) const
{
    byte_vector temp = pin;
    // verifyPin(*card, AUTH_PIN_REFERENCE, pin, authPinMinMaxLength().first, 0, 0);
    return internalAuthenticate(*card, hash, name());
}

ElectronicID::PinRetriesRemainingAndMax CustomJavaCard::authPinRetriesLeftImpl() const
{
    //return pinRetriesLeft(AUTH_PIN_REFERENCE);
    return {3, 3};
}

const std::set<SignatureAlgorithm>& CustomJavaCard::supportedSigningAlgorithms() const
{
    const static std::set<SignatureAlgorithm> ES_ALGOS = {SignatureAlgorithm::ES384};
    return ES_ALGOS;
}

ElectronicID::Signature CustomJavaCard::signWithSigningKeyImpl(const byte_vector& pin,
                                                               const byte_vector& hash,
                                                               const HashAlgorithm hashAlgo) const
{
    byte_vector temp = pin;
    // verifyPin(*card, SIGNING_PIN_REFERENCE, pin, signingPinMinMaxLength().first, 0, 0);
    return {computeSignature(*card, hash, name()), {SignatureAlgorithm::ES384, hashAlgo}};
}

ElectronicID::PinRetriesRemainingAndMax CustomJavaCard::signingPinRetriesLeftImpl() const
{
    // return pinRetriesLeft(SIGNING_PIN_REFERENCE);
    return {3, 3};
}

ElectronicID::PinRetriesRemainingAndMax
CustomJavaCard::pinRetriesLeft(byte_vector::value_type pinReference) const
{
    const pcsc_cpp::CommandApdu GET_DATA {
        0x00, 0xCB, 0x00, 0xFF, {0xA0, 0x03, 0x83, 0x01, pinReference}};
    const auto response = card->transmit(GET_DATA);
    if (!response.isOK()) {
        THROW(SmartCardError,
              "Command GET DATA failed with error " + pcsc_cpp::bytes2hexstr(response.toBytes()));
    }
    return {uint8_t(response.data[20]), int8_t(5)};
}

} // namespace electronic_id
