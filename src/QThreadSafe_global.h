#ifndef QTHREADSAFE_GLOBAL_H
#define QTHREADSAFE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QTHREADSAFE_LIBRARY)
#define QTHREADSAFE_EXPORT Q_DECL_EXPORT
#else
#define QTHREADSAFE_EXPORT Q_DECL_IMPORT
#endif

#endif // QTHREADSAFE_GLOBAL_H
