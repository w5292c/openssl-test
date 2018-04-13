TEMPLATE=app

QT -= gui
QT += core

CONFIG += link_pkgconfig

PKGCONFIG += libcrypto

HEADERS=\
  utils.h

SOURCES= \
  main.cpp \
  utils.cpp
