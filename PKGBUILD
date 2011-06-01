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
	config.h \
	dwm-5.8.2-bstack.diff \
	dwm-5.8.2-cellwriter.diff \
	dwm-5.8.2-uselessgap.diff \
	dwm-5.8-pango.patch \
	dwm-5.7.2-attachaside.diff \
	dwm-fancybarclickable.diff \
	focusmaster.c \
	push.c \
	tilemovemouse.c)
md5sums=('f0b422bfeaa812d66c6dd15c3cc92a6b'
         '939f403a71b6e85261d09fc3412269ee'
         '39a557beb09afe4e727bc4aed64b2cd6'
         'a1c3c37e349c324012ce8d6e967fd4cc'
         '136cc33ae7622f662d6598950b05be98'
         '94f282dcf82da679ff5ea9c86b51ec10'
         'a8470c8481e68dd4afb1293ae0520383'
         'a92ee04c33b1082da61b55d3617249eb'
         'ea991e765cd8da5b2f3dfb6a0832bd89'
         '52b9003105327b296ff9331d7c92b4f7'
         '689534c579b1782440ddcaf71537d8fd')

build() {
  cd $srcdir/$pkgname-$pkgver

  cp $srcdir/config.h config.h
  cp $srcdir/focusmaster.c focusmaster.c
  cp $srcdir/push.c push.c
  cp $srcdir/tilemovemouse.c tilemovemouse.c

  sed -i 's/CPPFLAGS =/CPPFLAGS +=/g' config.mk
  sed -i 's/CFLAGS =/CFLAGS +=/g' config.mk
  sed -i 's/LDFLAGS =/LDFLAGS +=/g' config.mk

  patch -p1 -i $srcdir/dwm-5.8-pango.patch || return 1
  patch -p1 -i $srcdir/dwm-fancybarclickable.diff || return 1
  patch -p1 -i $srcdir/dwm-5.7.2-attachaside.diff || return 1
  patch -p1 -i $srcdir/dwm-5.8.2-bstack.diff || return 1
  patch -p1 -i $srcdir/dwm-5.8.2-cellwriter.diff || return 1
  patch -p1 -i $srcdir/dwm-5.8.2-uselessgap.diff || return 1

  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11 || return 1
  make PREFIX=/usr DESTDIR=$pkgdir install || return 1
}

package() {
  install -m644 -D $srcdir/$pkgname-$pkgver/LICENSE $pkgdir/usr/share/licenses/$pkgname/LICENSE && \
  install -m644 -D $srcdir/$pkgname-$pkgver/README $pkgdir/usr/share/doc/$pkgname/README && \
  install -m644 -D $srcdir/dwm.desktop $pkgdir//etc/X11/sessions/dwm.desktop
}
