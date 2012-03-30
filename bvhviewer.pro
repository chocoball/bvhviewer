#-------------------------------------------------
#
# Project created by QtCreator 2012-03-30T17:08:47
#
#-------------------------------------------------

QT			+= core gui

TARGET		= bvhviewer
TEMPLATE	= app


SOURCES		+=	src/main.cpp			\
				src/mainwindow.cpp		\
				src/bvh/cbvh.cpp		\
				src/bvh/cbvhnode.cpp	\
				src/bvh/cbvhmotion.cpp	\
				src/bvh/cbvhloader.cpp

HEADERS		+=	src/mainwindow.h		\
				src/bvh/cbvh.h			\
				src/bvh/cbvhnode.h		\
				src/bvh/cbvhmotion.h	\
				src/bvh/cbvhloader.h

FORMS		+=	ui/mainwindow.ui
