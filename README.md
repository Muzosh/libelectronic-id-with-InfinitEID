# libelectronic-id-with-custom-java-card
* this repository is the fork of [web-eid/libelectronic-id](https://github.com/web-eid/libelectronic-id)
* it includes the CustomJavaCard implementation so web-eid-app can work with TODO URL

## Installation
### Initialize Web-eID native application with CustomJavaCard implementation submodule
* `git clone https://github.com/web-eid/web-eid-app; cd web-eid-app`
* `git submodule set-url lib/libelectronic-id https://github.com/Muzosh/libelectronic-id-with-custom-java-card.git`
* `git submodule update --init --remote --recursive`

### Build modified Web-eID native application
* follow the build instructions in [official Web-eID repository](https://github.com/web-eid/web-eid-app#building-and-testing)
* builded app will work with CustomJavaCard
