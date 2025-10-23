#ifndef NFC_NDEF_GLOBAL_H
#define NFC_NDEF_GLOBAL_H

#include <QtCore/QtGlobal>

#if defined(NFC_NDEF_LIBRARY)
#  define NFC_NDEFSHARED_EXPORT Q_DECL_EXPORT
#else
#  define NFC_NDEFSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // NFC_NDEF_GLOBAL_H
