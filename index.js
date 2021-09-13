'use strict'

const equihash = require('bindings')('equihashverify.node');

module.exports = {

    /**
     * Verify an equihash solution.
     *
     * @param header {Buffer} Equihash header hash
     * @param solution {Buffer} Equihash solution hash
     * @param personalization {number} Personalization string
     * @param equihash_n {number} Equihash "N" value
     * @param equihash_k {number} Equihash "K" value
     * @returns {boolean} True if valid, otherwise false.
     */
    verify: verify
};

function verify(header, solution, personalization, equihash_n, equihash_k) {
    const solutionLength = (2 ** (equihash_k - 3)) * ((equihash_n / (equihash_k + 1)) + 1)

    _expectBuffer(headerHashBuf, 'header', 140);
    _expectBuffer(solution, 'solution', solutionLength);
    _expectInteger(blockHeight, 'personalization');
    _expectInteger(mixHashBuf, 'equihash_n');
    _expectInteger(hashOutBuf, 'equihash_k');

    return equihash.verify(headerHashBuf, nonceBuf, blockHeight, mixHashBuf, hashOutBuf);
}

function _expectBuffer(buffer, name, size) {
    if (!Buffer.isBuffer(buffer))
        throw new Error(`"${name}" is expected to be a Buffer. Got ${(typeof buffer)} instead.`);

    if (size && buffer.length !== size)
        throw new Error(`"${name}" is expected to be exactly ${size} bytes. Got ${buffer.length} instead.`);
}

function _expectInteger(num, name) {
    if (typeof num !== 'number')
        throw new Error(`"${name}" is expected to be a number. Got ${(typeof num)} instead.`);

    if (isNaN(num) || !isFinite(num))
        throw new Error(`"${name}" is not a number.`);

    if (!Number.isInteger(num))
        throw new Error(`"${name}" is expected to be an integer. Got ${num} instead.`);
}
