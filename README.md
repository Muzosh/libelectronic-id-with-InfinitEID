# libelectronic-id-with-InfinitEID
* this repository is the fork of [web-eid/libelectronic-id](https://github.com/web-eid/libelectronic-id)
* it includes the InfinitEID implementation so web-eid-app can work with [InfinitEID applet](https://github.com/Muzosh/InfinitEID)

## Installation
### Initialize Web-eID native application with InfinitEID implementation submodule
* `git clone https://github.com/web-eid/web-eid-app; cd web-eid-app`
* `git submodule set-url lib/libelectronic-id https://github.com/Muzosh/libelectronic-id-with-InfinitEID.git`
* `git submodule update --init --remote --recursive`

### Build modified Web-eID native application
* follow the build instructions in [official Web-eID repository](https://github.com/web-eid/web-eid-app#building-and-testing)
* builded app will work with InfinitEID
* for example, on MacOS you can replace the official Web-eID.app installed from [here](https://web-eid.eu/) by builded application from `./build/src/app/Web-eID.app`
