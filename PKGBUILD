# $Id: PKGBUILD 18861 2010-06-16 09:09:52Z spupykin $
# Maintainer: Sergej Pupykin <pupykin.s+arch@gmail.com>
# Contributor: Dag Odenhall <dag.odenhall@gmail.com>
# Contributor: Grigorios Bouzakis <grbzks@gmail.com>

pkgname=dwm
pkgver=5.8.2
pkgrel=2
pkgdesc="A dynamic window manager for X"
url="http://dwm.suckless.org"
arch=('i686' 'x86_64')
license=('MIT')
options=(zipman)
depends=('libx11' 'libxinerama')
install=dwm.install
source=(http://dl.suckless.org/dwm/dwm-$pkgver.tar.gz \
	dwm.desktop \
	dwm-5.8.2-combined.diff \
	config.h)

build() {
  cd $srcdir/$pkgname-$pkgver

  cp $srcdir/config.h config.h

  sed -i 's/CPPFLAGS =/CPPFLAGS +=/g' config.mk
  sed -i 's/CFLAGS =/CFLAGS +=/g' config.mk
  sed -i 's/LDFLAGS =/LDFLAGS +=/g' config.mk

  patch -p1 -i $srcdir/dwm-5.8.2-combined.diff || return 1

  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11 || return 1
  make PREFIX=/usr DESTDIR=$pkgdir install || return 1
}

package() {
  install -m644 -D $srcdir/$pkgname-$pkgver/LICENSE $pkgdir/usr/share/licenses/$pkgname/LICENSE && \
  install -m644 -D $srcdir/$pkgname-$pkgver/README $pkgdir/usr/share/doc/$pkgname/README && \
  install -m644 -D $srcdir/dwm.desktop $pkgdir//etc/X11/sessions/dwm.desktop
}
