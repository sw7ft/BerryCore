/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QMALGORITHMS_H
#define QMALGORITHMS_H

#include "qmobilitysubset.h"

QTMS_BEGIN_NAMESPACE

/*
  This performs a partial sort, examining the elements in the range [start, end-1] to place the
  elements of ordinality [from, to-1] in the positions [from, to-1] in order defined by lessThan.
  In addition, after calling this function, elements lesser than *from will appear before "from" and
  elements greater than *(to-1) will appear at or after "to".

  This function runs in time O(k log k + N), where k = to-from, N = end-start.  It uses an in-place
  partial quicksort algorithm.  See:
    http://en.wikipedia.org/wiki/Selection_algorithm

  Some examples using the convenience function for containers:

  QList<int> list1 = ..., list2 = ...;

  qPartialSort(list1, 0, 10);
  QList<int> firstTen = list1.mid(0, 10);
  qPartialSort(list1, 10, 20);
  QList<int> secondTen = list1.mid(10, 10);
  qPartialSort(list1, 20, list1.size());
  QList<int> rest = list.mid(20);
  // list1 is now sorted!

  int mid = list2.count() / 2;
  qPartialSort(list2, mid, mid+1);  // O(N) time
  int median = list2[mid];
  */
template<typename RandomAccessIterator, typename LessThan>
inline void qPartialSort(RandomAccessIterator start, RandomAccessIterator end,
        RandomAccessIterator from, RandomAccessIterator to, LessThan lessThan)
{
    // This code is based on qSort
    while (true) {
        if (from < start)
            from = start;
        if (to > end)
            to = end;

        int span = int(end - start);
        if (span < 2 || from >= to)
            return;

        --end;
        RandomAccessIterator low = start, high = end - 1;
        RandomAccessIterator pivot = start + span / 2;

        if (lessThan(*end, *start))
            qSwap(*end, *start);
        if (span == 2)
            return;

        if (lessThan(*pivot, *start))
            qSwap(*pivot, *start);
        if (lessThan(*end, *pivot))
            qSwap(*end, *pivot);
        if (span == 3)
            return;

        qSwap(*pivot, *end);

        // Partition the elements
        while (low < high) {
            while (low < high && lessThan(*low, *end))
                ++low;

            while (high > low && lessThan(*end, *high))
                --high;

            if (low < high) {
                qSwap(*low, *high);
                ++low;
                --high;
            } else {
                break;
            }
        }
        if (lessThan(*low, *end))
            pivot = low+1;
        else
            pivot = low;

        qSwap(*end, *pivot);
        ++end;

        // *pivot is now in the correct place in the list
        if (pivot > to) {
            // like qPartialSort(start, pivot, from, to, lessThan);
            end = pivot;
        } else if (pivot > from) { // from < pivot <= to
            qSort(start, pivot, lessThan);
            // like qPartialSort(pivot+1, end, pivot+1, to, lessThan);
            start = pivot + 1;
            from = pivot + 1;
        } else { // pivot <= from < to
            // like qPartialSort(pivot+1, end, from, to, lessThan);
            start = pivot+1;
        }
    }
}

template<typename RandomAccessIterator, typename T>
inline void qPartialSortHelper(RandomAccessIterator start, RandomAccessIterator end,
        RandomAccessIterator from, RandomAccessIterator to, const T& dummy)
{
    Q_UNUSED(dummy);
    qPartialSort(start, end, from, to, qLess<T>());
}

template<typename RandomAccessIterator>
inline void qPartialSort(RandomAccessIterator start, RandomAccessIterator end,
        RandomAccessIterator from, RandomAccessIterator to)
{
    qPartialSortHelper(start, end, from, to, *start);
}

template<typename Container>
inline void qPartialSort(Container& container, int from, int to)
{
    qPartialSort(container.begin(), container.end(), container.begin()+from, container.begin()+to);
}

QTMS_END_NAMESPACE

#endif
