
# DGHV Encryption library

The DGHV encryption library that uses a SHE scheme. The crypto library offers the following functionality:

  - Secret key generation
  - Public key generation
  - Bit and string encryption
  - Bit and string decryption
  - Bit and string evaluation

### Tech

The encryption library uses a number of open source projects to work properly:

* [GMP] - Arbitary large number computation and storage.
* [Python3.6] - Statistical test files.
* [Numpy] - Package for scientific computing with Python.
* [PyLab] - Package to generate plots.


### Compilation


```sh
$ cd Almanac/src
$ make
```

Test debugging files

```sh
$ cd Almanac/src
$ make crypTest
```

Statistical test
```sh
$ cd Almanac/src
$ make static
```
Visual test file
```sh
$ cd Almanac/src
$ make check
```
Cleanup
```sh
$ cd Almanac/src
$ make clean
```

**Free Software**

[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)


   [GMP]: <https://gmplib.org/>
   [Python3.6]: <https://www.python.org/downloads/>
   [Numpy]: <http://www.numpy.org/>
   [PyLab]: <https://scipy.github.io/old-wiki/pages/PyLab>
