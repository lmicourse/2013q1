#ifndef QTNET_GLOBAL_H
#define QTNET_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QTNET_LIBRARY)
#  define QTNETSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QTNETSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QTNET_GLOBAL_H
