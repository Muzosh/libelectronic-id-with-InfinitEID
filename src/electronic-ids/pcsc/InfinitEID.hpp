#pragma once

#include "PcscElectronicID.hpp"

namespace electronic_id
{

class InfinitEID : public PcscElectronicID
{
public:
    InfinitEID(pcsc_cpp::SmartCard::ptr _card) : PcscElectronicID(std::move(_card)) {}

private:
    pcsc_cpp::byte_vector getCertificateImpl(const CertificateType type) const override;

    JsonWebSignatureAlgorithm authSignatureAlgorithm() const override
    {
        return JsonWebSignatureAlgorithm::ES384;
    }
    PinMinMaxLength authPinMinMaxLength() const override { return {4, 12}; }
    PinRetriesRemainingAndMax authPinRetriesLeftImpl() const override;

    const std::set<SignatureAlgorithm>& supportedSigningAlgorithms() const override;
    PinMinMaxLength signingPinMinMaxLength() const override { return {6, 12}; }
    PinRetriesRemainingAndMax signingPinRetriesLeftImpl() const override;

    std::string name() const override { return "InfinitEID"; }
    Type type() const override { return InfEID; }

    pcsc_cpp::byte_vector signWithAuthKeyImpl(const pcsc_cpp::byte_vector& pin,
                                              const pcsc_cpp::byte_vector& hash) const override;

    Signature signWithSigningKeyImpl(const pcsc_cpp::byte_vector& pin,
                                     const pcsc_cpp::byte_vector& hash,
                                     const HashAlgorithm hashAlgo) const override;

    pcsc_cpp::byte_vector sign(const HashAlgorithm hashAlgo, const pcsc_cpp::byte_vector& hash,
                               const pcsc_cpp::byte_vector& pin,
                               pcsc_cpp::byte_vector::value_type pinReference,
                               PinMinMaxLength pinMinMaxLength,
                               pcsc_cpp::byte_vector::value_type keyReference,
                               pcsc_cpp::byte_vector::value_type signatureAlgo,
                               pcsc_cpp::byte_vector::value_type LE) const;

    PinRetriesRemainingAndMax pinRetriesLeft(pcsc_cpp::byte_vector::value_type pinReference) const;
};

} // namespace electronic_id
