# Foundation Equihash

[![Foundation CI](https://github.com/blinkhash/foundation-equihash/actions/workflows/build.yml/badge.svg?branch=master)](https://github.com/blinkhash/foundation-equihash/actions/workflows/build.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Downloads](https://img.shields.io/npm/dm/foundation-equihash.svg)](https://www.npmjs.com/package/foundation-equihash)
[![Version](https://img.shields.io/npm/v/foundation-equihash.svg)](https://www.npmjs.com/package/foundation-equihash)
[![Known Vulnerabilities](https://snyk.io/test/npm/foundation-equihash/badge.svg)](https://snyk.io/test/npm/foundation-equihash)
[![Discord](https://img.shields.io/discord/738590795384356904)](https://discord.gg/8xtHZFKJQY)

This is a Node module for simple hashing and verifying inputs using the
Equihash proof-of-work algorithm as implemented by [ZCash](https://github.com/zcash/zcash/releases/tag/v4.4.1). Most of the native code comes from or is adapted from [ZCash code](https://github.com/zcash/zcash). This module has been developed and tested on [Node v10.16.3](https://nodejs.org/) and
[Ubuntu 16.04](http://releases.ubuntu.com/16.04/).

#### Need Support?

If you need help with a code-related matter, the first place to look is our [Discord](https://discord.gg/8xtHZFKJQY), where the developers will be available to answer any questions. However, please do not come to me with issues regarding setup. Use Google and the existing documentation for that.

---

### Install & Test
````
curl -sL https://deb.nodesource.com/setup_10.x | sudo -E bash -
sudo apt-get install nodejs -y
sudo apt-get install build-essential libsodium-dev libboost-system-dev
git clone https://github.com/Blinkhash/foundation-equihash.git
cd foundation-equihash
sudo npm install -g mocha
npm install && npm test
````

---

### Usage

````javascript
var ev = require('bindings')('equihashverify.node');
var header = new Buffer(..., 'hex');
var solution = new Buffer(..., 'hex'); //do not include byte size preamble "fd4005"
ev.verify(header, solution, n, k);
//returns boolean
````

````javascript
ev.verify(header, solution);
````

### Donations

Maintaining this project has always been driven out of nothing more than a desire to give back to the mining community, however I always appreciate donations, especially if this repository helps you in any way.

- Bitcoin: 3EbrVYLxN5WeQmPpL6owo3A7rJELXecbbc
- Ethereum: 0xd3e3daED621d228244Fa89A3dd8AF07B52E72319
- Litecoin: MFWpARrSADAy3Qj79C4pSasS9F156QipwC
- ZCash: t1NSk8gyiou8TxWRZTVuUkfM5f9riopN58A

---

### License

Released under the MIT License. See https://opensource.org/licenses/MIT for more information

---
