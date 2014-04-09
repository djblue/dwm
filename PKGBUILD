# Maintainer: Abdullah Badahdah <a.s.badahdah@gmail.com>

pkgname=dwm.git
pkgver=6.0
pkgrel=1
pkgdesc="Custom dwm build from personal git repo."
arch=('i686' 'x86_64')
url="http://git.djblue.us.to:8080/dwm/"
license=('MIT')
depends=('libx11' 'libxinerama')
makedepends=('git')
conflicts=('dwm')
provides=('dwm')
install=
md5sums=('SKIP')

_gitroot='djblue.us:git/'
_gitname='dwm'

build() {
  cd "$srcdir"
  msg "Connecting to GIT server...."

  if [[ -d "$_gitname" ]]; then
    cd "$_gitname" && git pull origin
    msg "The local files are updated."
  else
    git clone "$_gitroot$_gitname"
  fi

  msg "GIT checkout done or server timeout"
  msg "Starting build..."

  rm -rf "$srcdir/$_gitname-build"
  git clone "$srcdir/$_gitname" "$srcdir/$_gitname-build"
  cd "$srcdir/$_gitname-build"

  #
  # BUILD HERE
  #
  make
}

package() {
  cd "$srcdir/$_gitname-build"
  make DESTDIR="$pkgdir/" install
}

# vim:set ts=2 sw=2 et:
