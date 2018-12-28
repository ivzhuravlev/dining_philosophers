#pragma once

#include <QtCore/qglobal.h>

#ifdef DPHCORE_LIB

#define DPHCORE_EXPORT Q_DECL_EXPORT

#else

#define DPHCORE_EXPORT Q_DECL_IMPORT

#endif