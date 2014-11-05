# glSpiders

<a href="https://github.com/drmats/glSpiders/">
    <img
        src="https://raw.githubusercontent.com/drmats/glSpiders/master/icon.png"
        align="left"
        hspace="10"
    >
</a>

A _very simple_ [OpenGL](http://www.opengl.org/) animation app.

Wireframe spiders on a flat grid with rotating camera around.<br>
No lights. No textures. No shadows. No depth buffer.

Original code written in 2005.




## installation

Clone the repository and invoke compilation:

    $ git clone https://github.com/drmats/glSpiders.git
    $ cd glSpiders
    
* on linux:

        $ make linux

* on windows:

        > make windows

_to build statically linked windows executable:_

    > make win_static




## usage

    $ ./glSpiders
    glSpiders v. 0.0.1
      [f] - full screen toggle
      [q] - quit




## dependencies

* C compiler with good
  [**ISO C99** (ISO/IEC 9899:1999)](https://en.wikipedia.org/wiki/C99)
  support (any _maintained_ version of [**gcc**](http://gcc.gnu.org/) will do)
* [**GNU Make**](http://www.gnu.org/software/make/)
* [GLUT](http://www.opengl.org/resources/libraries/glut/)-compatible library
  (i.e. [**freeglut**](http://freeglut.sourceforge.net/))

### windows-specific

* [**MinGW**](http://www.mingw.org/)
* [freeglut windows development binaries](http://www.transmissionzero.co.uk/software/freeglut-devel/)




## license

**glSpiders** are released under the BSD 2-Clause license. See the
[LICENSE](https://raw2.github.com/drmats/glSpiders/master/LICENSE)
for more details.
