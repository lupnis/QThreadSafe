#ifndef QTHREADSAFEVARS_H
#define QTHREADSAFEVARS_H

#include <QMutex>
#include "QThreadSafe_global.h"

#include <QString>
#include <QVariant>

class QTHREADSAFE_EXPORT QThreadSafeVariant {
   public:
    QThreadSafeVariant() {}
    QThreadSafeVariant(const QThreadSafeVariant& rvalue) {
        this->qvariant = rvalue.get();
    }
    template <class T>
    QThreadSafeVariant(const T& rvalue) {
        this->qvariant = QVariant(rvalue);
    }
    ~QThreadSafeVariant() {}
    template <class T>
    inline void set(const T& rvalue) {
        QMutexLocker locker(&this->lock);
        this->qvariant = QVariant(rvalue);
    }
    template <class T>
    QThreadSafeVariant& operator=(const T& rvalue) {
        this->set(rvalue);
        return *this;
    }
    operator QVariant() const { return this->get(); }
    inline QVariant get() const {
        QMutexLocker locker(&this->lock);
        return this->qvariant;
    }

   protected:
    QVariant qvariant;
    mutable QMutex lock;
};

template <typename T>
class QTHREADSAFE_EXPORT QThreadSafeMetaType {
   public:
    QThreadSafeMetaType() {}
    QThreadSafeMetaType(const T& rvalue) { this->value = rvalue; }
    QThreadSafeMetaType(const QThreadSafeMetaType& rvalue) {
        this->value = rvalue.get();
    }
    ~QThreadSafeMetaType() {}
    inline void set(const T& rvalue) {
        QMutexLocker locker(&this->lock);
        this->value = rvalue;
    }
    QThreadSafeMetaType& operator=(const T& rvalue) {
        this->set(rvalue);
        return *this;
    }
    operator T() { return this->get(); }
    inline T get() const {
        QMutexLocker locker(&this->lock);
        return this->value;
    }

   protected:
    T value;
    mutable QMutex lock;
};

typedef QThreadSafeMetaType<qint8> QTSInt8;
typedef QThreadSafeMetaType<qint16> QTSInt16;
typedef QThreadSafeMetaType<qint32> QTSInt32;
typedef QThreadSafeMetaType<qint64> QTSInt64;
typedef QThreadSafeMetaType<qint128> QTSInt128;
typedef QThreadSafeMetaType<qsizetype> QTSSizeType;
typedef QThreadSafeMetaType<quint8> QTSUInt8;
typedef QThreadSafeMetaType<quint16> QTSUInt16;
typedef QThreadSafeMetaType<quint32> QTSUInt32;
typedef QThreadSafeMetaType<quint64> QTSUInt64;
typedef QThreadSafeMetaType<quint128> QTSUInt128;
typedef QThreadSafeMetaType<qfloat16> QTSFloat16;
typedef QThreadSafeMetaType<bool> QTSBool;
typedef QThreadSafeMetaType<char> QTSChar;
typedef QThreadSafeMetaType<short> QTSShort;
typedef QThreadSafeMetaType<int> QTSInt;
typedef QThreadSafeMetaType<long> QTSLong;
typedef QThreadSafeMetaType<long long> QTSLongLong;
typedef QThreadSafeMetaType<unsigned short> QTSUShort;
typedef QThreadSafeMetaType<unsigned int> QTSUInt;
typedef QThreadSafeMetaType<unsigned long> QTSULong;
typedef QThreadSafeMetaType<unsigned long long> QTSULongLong;
typedef QThreadSafeMetaType<float> QTSFloat;
typedef QThreadSafeMetaType<double> QTSDouble;

typedef QThreadSafeMetaType<qint8*> QTSInt8Ptr;
typedef QThreadSafeMetaType<qint16*> QTSInt16Ptr;
typedef QThreadSafeMetaType<qint32*> QTSInt32Ptr;
typedef QThreadSafeMetaType<qint64*> QTSInt64Ptr;
typedef QThreadSafeMetaType<qint128*> QTSInt128Ptr;
typedef QThreadSafeMetaType<qsizetype*> QTSSizeTypePtr;
typedef QThreadSafeMetaType<quint8*> QTSUInt8Ptr;
typedef QThreadSafeMetaType<quint16*> QTSUInt16Ptr;
typedef QThreadSafeMetaType<quint32*> QTSUInt32Ptr;
typedef QThreadSafeMetaType<quint64*> QTSUInt64Ptr;
typedef QThreadSafeMetaType<quint128*> QTSUInt128Ptr;
typedef QThreadSafeMetaType<qfloat16*> QTSFloat16Ptr;
typedef QThreadSafeMetaType<bool*> QTSBoolPtr;
typedef QThreadSafeMetaType<char*> QTSCharPtr;
typedef QThreadSafeMetaType<short*> QTSShortPtr;
typedef QThreadSafeMetaType<int*> QTSIntPtr;
typedef QThreadSafeMetaType<long*> QTSLongPtr;
typedef QThreadSafeMetaType<long long*> QTSLongLongPtr;
typedef QThreadSafeMetaType<unsigned short*> QTSUShortPtr;
typedef QThreadSafeMetaType<unsigned int*> QTSUIntPtr;
typedef QThreadSafeMetaType<unsigned long*> QTSULongPtr;
typedef QThreadSafeMetaType<unsigned long long*> QTSULongLongPtr;
typedef QThreadSafeMetaType<float*> QTSFloatPtr;
typedef QThreadSafeMetaType<double*> QTSDoublePtr;
typedef QThreadSafeMetaType<void*> QTSVoidPtr;

template <class T = QThreadSafeVariant>
class QTHREADSAFE_EXPORT QThreadSafeList {
   public:
    QThreadSafeList() {}
    QThreadSafeList(const QThreadSafeList& rvalue) {
        this->qlist = rvalue.get();
    }
    QThreadSafeList(const QList<T>& rvalue) { this->qlist = rvalue; }
    ~QThreadSafeList() {}
    inline void set(const QList<T>& rvalue) {
        QMutexLocker locker(&this->lock);
        this->qlist = rvalue;
    }
    inline void set(int index, const T& value) {
        QMutexLocker locker(&this->lock);
        this->qlist[index] = value;
    }
    QThreadSafeList& operator=(const QList<T>& rvalue) {
        this->set(rvalue);
        return *this;
    }
    inline void pushBack(const T& value) {
        QMutexLocker locker(&this->lock);
        this->qlist.push_back(value);
    }
    inline void pushFront(const T& value) {
        QMutexLocker locker(&this->lock);
        this->qlist.push_front(value);
    }
    inline void popBack() {
        QMutexLocker locker(&this->lock);
        this->qlist.pop_back();
    }
    inline void popFront() {
        QMutexLocker locker(&this->lock);
        this->qlist.pop_front();
    }
    inline void clear() {
        QMutexLocker locker(&this->lock);
        this->qlist.clear();
    }
    inline void removeAt(qsizetype index) {
        QMutexLocker locker(&this->lock);
        this->qlist.removeAt(index);
    }
    inline void insertAt(qsizetype index, const T& value) {
        QMutexLocker locker(&this->lock);
        this->qlist.insert(index, value);
    }
    inline void append(const T& value) {
        QMutexLocker locker(&this->lock);
        this->qlist.append(value);
    }
    inline void append(const QList<T>& value) {
        QMutexLocker locker(&this->lock);
        this->qlist.append(value);
    }
    inline void append(const QThreadSafeList& value) {
        QMutexLocker locker(&this->lock);
        this->qlist.append(value.get());
    }
    inline void prepend(const T& value) {
        QMutexLocker locker(&this->lock);
        this->qlist.prepend(value);
    }
    inline T takeAt(qsizetype index) const {
        QMutexLocker locker(&this->lock);
        return this->qlist.takeAt(index);
    }
    inline void removeFirst() {
        QMutexLocker locker(&this->lock);
        this->qlist.removeFirst();
    }
    inline void removeLast() {
        QMutexLocker locker(&this->lock);
        this->qlist.removeLast();
    }
    inline qsizetype removeAll(const T& value) {
        QMutexLocker locker(&this->lock);
        return this->qlist.removeAll(value);
    }
    inline void reserve(qsizetype size) {
        QMutexLocker locker(&this->lock);
        this->qlist.reserve(size);
    }
    inline void squeeze() {
        QMutexLocker locker(&this->lock);
        this->qlist.squeeze();
    }
    inline T first() const {
        QMutexLocker locker(&this->lock);
        return this->qlist.first();
    }
    inline T begin() const { return this->first(); }
    inline T cbegin() const { return this->first(); }
    inline T rend() const { return this->first(); }
    inline T last() const {
        QMutexLocker locker(&this->lock);
        return this->qlist.last();
    }
    inline T end() const { return this->last(); }
    inline T cend() const { return this->last(); }
    inline T rbegin() const { return this->last(); }
    inline qsizetype size() const {
        QMutexLocker locker(&this->lock);
        return this->qlist->size();
    }
    inline qsizetype length() const { return this->size(); }
    inline bool empty() const { return !this->size(); }
    inline bool isEmpty() const { return !this->size(); }
    inline qsizetype capacity() const {
        QMutexLocker locker(&this->lock);
        return this->qlist.capacity();
    }
    inline QList<T> get() const {
        QMutexLocker locker(&this->lock);
        return this->qlist;
    }
    inline T at(qsizetype index) const {
        QMutexLocker locker(&this->lock);
        return this->qlist.at(index);
    }
    operator QList<T>() const { return this->get(); }
    inline bool contains(const T& value) const {
        QMutexLocker locker(&this->lock);
        return this->qlist.contains(value);
    }
    inline qsizetype indexOf(const T& value, qsizetype offset = 0) const {
        QMutexLocker locker(&this->lock);
        return this->qlist.indexOf(value, offset);
    }
    inline qsizetype lastIndexOf(const T& value, qsizetype offset = -1) const {
        QMutexLocker locker(&this->lock);
        return this->qlist.lastIndexOf(value, offset);
    }
    inline qsizetype count(const T& value) {
        QMutexLocker locker(&this->lock);
        return this->qlist.count(value);
    }

   protected:
    QList<T> qlist;
    mutable QMutex lock;
};

#endif  // QTHREADSAFE_H
