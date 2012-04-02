#-------------------------------------------------
#
# Project created by QtCreator 2012-03-30T17:08:47
#
#-------------------------------------------------

QT			+= core gui opengl

TARGET		= bvhviewer
TEMPLATE	= app


SOURCES		+=	src/main.cpp			\
				src/mainwindow.cpp		\
				src/bvh/cbvh.cpp		\
				src/bvh/cbvhnode.cpp	\
				src/bvh/cbvhmotion.cpp	\
				src/bvh/cbvhloader.cpp	\
				src/cbvhmodel.cpp		\
				src/cbvhitem.cpp		\
				src/cglview.cpp

HEADERS		+=	src/mainwindow.h		\
				src/bvh/cbvh.h			\
				src/bvh/cbvhnode.h		\
				src/bvh/cbvhmotion.h	\
				src/bvh/cbvhloader.h	\
				src/cbvhmodel.h			\
				src/cbvhitem.h			\
				src/cglview.h

FORMS		+=	ui/mainwindow.ui
