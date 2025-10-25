# -*- coding: iso-8859-1 -*-
# Pretty-printers for Qt4.
 
# Copyright (C) 2009 Niko Sams <niko.sams@gmail.com>
 
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
import gdb
import itertools
import re
import sys

 
# Try to use the new-style pretty-printing if available.
_use_gdb_pp = True
try:
    import gdb.printing
except ImportError:
    _use_gdb_pp = False

REF_LIMIT  = 512
SIZE_LIMIT = 512

class QStringPrinter:
 
    def __init__(self, val):
        self.val = val
 
    def to_string(self):
    	# Leveraging available reference counter to determine if object is initialized or not.
        try:
            ref = self.val['d']['ref'] 
            #let's do check ref['_q_value'] for value. if num in shared pointer is skyrocketing, there's something wrong
            if ref['_q_value'] > 0 and ref['_q_value'] < REF_LIMIT: 
                    size = self.val['d']['size']    		    		
                    if size < 0 : return "not initialized."
                    if size == 0 : return "\"\""
                    data = self.val['d']['data'] 
                    if size > SIZE_LIMIT :    
                            #python can at its best return only UTF-8!!!
                            return '\"{0}...\" [Addr: {1}]'.format(data.cast(lookupType("char").pointer()).string(encoding = 'UTF-16', errors='ignore', length = (maxSize - 3) * 2).encode('utf-8'), data.address)
                    return '\"{0}\"'.format(data.cast(lookupType("char").pointer()).string(encoding = 'UTF-16', errors='ignore', length = self.val['d']['size'] * 2).encode('utf-8'))
            return "Not initialized."
        except:
            return "Not initialized."

class QByteArrayPrinter:
 
    def __init__(self, val):
        self.val = val
 
    class _iterator:
        def __init__(self, data, size):
            self.data = data
            self.size = size
            self.count = 0
 
        def __iter__(self):
            return self
 
        def next(self):
            if self.count >= self.size or self.data == None:
                raise StopIteration
            count = self.count
            self.count = self.count + 1
            try:
                return ('[%d]' % count, self.data[count])
            except:
                return ""
 
    def children(self):
        try:
            #first check for reference
            if isReferenceCorrect(self) == False:
                return self._iterator(None, 0)

            #second check for size
            size = 0;
            if isSizeCorrect(self) == False:
                size = SIZE_LIMIT;
            else:
                size = self.val['d']['size']

            return self._iterator(self.val['d']['data'], size)
        except:
            return self._iterator(None, 0)

    def to_string(self):    
        #todo: handle charset correctly
        try:
            if isSizeCorrect(self) == False:
                return "Array not initialized yet or too large to display"
            else:
                return self.val['d']['data'].string()
        except:
            return "Not initialized."
 
    def display_hint (self):
        return 'string'
 
class QListPrinter:
    "Print a QList"
 
    class _iterator:
        def __init__(self, nodetype, d):
            self.nodetype = nodetype
            self.d = d
            self.count = 0
 
        def __iter__(self):
            return self
 
        def next(self):
            if self.d == None:
                raise StopIteration
            try:
                if self.count >= self.d['end'] - self.d['begin']:
                    raise StopIteration
                count = self.count
                array = self.d['array'][self.d['begin'] + count]

                #from QTypeInfo::isLarge
                isLarge = self.nodetype.sizeof > lookupType('void').pointer().sizeof

                isPointer = self.nodetype.code == gdb.TYPE_CODE_PTR

                #unfortunately we can't use QTypeInfo<T>::isStatic as it's all inlined, so use
                #this list of types that use Q_DECLARE_TYPEINFO(T, Q_MOVABLE_TYPE)
                #(obviously it won't work for custom types)
                movableTypes = ['QRect', 'QRectF', 'QString', 'QMargins', 'QLocale', 'QChar', 'QDate', 'QTime', 'QDateTime', 'QVector',
                'QRegExpr', 'QPoint', 'QPointF', 'QByteArray', 'QSize', 'QSizeF', 'QBitArray', 'QLine', 'QLineF', 'QModelIndex', 'QPersitentModelIndex',
                'QVariant', 'QFileInfo', 'QUrl', 'QXmlStreamAttribute', 'QXmlStreamNamespaceDeclaration', 'QXmlStreamNotationDeclaration',
                'QXmlStreamEntityDeclaration']
                #this list of types that use Q_DECLARE_TYPEINFO(T, Q_PRIMITIVE_TYPE) (from qglobal.h)
                primitiveTypes = ['bool', 'char', 'signed char', 'uchar', 'short', 'ushort', 'int', 'uint', 'long', 'ulong', 'qint64', 'qunit64', 'float', 'double']
                if movableTypes.count(self.nodetype.tag) or primitiveTypes.count(str(self.nodetype)):
                    isStatic = False
                else:
                    isStatic = not isPointer

                if isLarge or isStatic: #see QList::Node::t()
                    node = array.cast(lookupType('QList<%s>::Node' % self.nodetype).pointer())
                else:
                    node = array.cast(lookupType('QList<%s>::Node' % self.nodetype))
                self.count = self.count + 1
                return ('[%d]' % count, node['v'].cast(self.nodetype))
            except:  
                raise StopIteration

    def __init__(self, val, container, itype):
        try:
            self.val = val
            self.container = container
            if itype == None:
                self.itype = self.val.type.template_argument(0)
            else:
                self.itype = lookupType(itype)

            try:
                if str(self.itype) == str(lookupType('QVariant')):
                    self.qvariant = True
                    self.val = None
                else:
                    self.qvariant = False
            except:
                self.qvariant = False

        except:
            self.val = None
            self.container = None
            self.itype = None

    def children(self):
        try:
            if self.val == None:
                return self._iterator(None, None)

            #first check for reference
            if isReferenceCorrect(self) == False:
                return self._iterator(None, None)

            #second check for size (this check is different to standard one)
            if self.val['d']['end'] - self.val['d']['begin'] > 512:
                return self._iterator(None, None)

            return self._iterator(self.itype, self.val['d'])
        except:
            return self._iterator(None, None)

    def to_string(self):
        if self.qvariant == True:
            return "QVariant types printing not supported"

        if self.val == None:
            return "Not initialized"
        
        try:
            #first check for reference
            if isReferenceCorrect(self) == False:
                return "Not initialized"

            #second check for size (this check is different to standard one)      
            if self.val['d']['end'] - self.val['d']['begin'] > 512:
                return "Not initialized or size too large to display"

            empty = ""
            if self.val['d']['end'] == self.val['d']['begin']:
                empty = "empty "

            return "%s%s<%s>" % ( empty, self.container, self.itype )
        except:
            return "Not initialized"

class QVectorPrinter:
    "Print a QVector"
 
    class _iterator:
        def __init__(self, nodetype, d, p):
            self.nodetype = nodetype
            self.d = d
            self.p = p
            self.count = 0
 
        def __iter__(self):
            return self
 
        def next(self):
            if self.d == None:
                raise StopIteration

            if self.count >= self.p['size']:
                raise StopIteration
            count = self.count
 
            self.count = self.count + 1
            return ('[%d]' % count, self.p['array'][count])
 
    def __init__(self, val, container):
        try:
            self.val = val
            self.container = container
            self.itype = self.val.type.template_argument(0)
        except:
            self.d = None
            self.container = None
            self.itype = None
 
    def children(self):
        try:
            if self.val == None:
                return self._iterator(None, None, None)

            #first check for reference
            if isReferenceCorrect(self) == False:
                return self._iterator(None, None, None)

            #second check for size        
            if isSizeCorrect(self) == False:
                return self._iterator(None, None, None)

            return self._iterator(self.itype, self.val['d'], self.val['p'])
        except:
            return self._iterator(None, None, None)
 
    def to_string(self):
        if self.val == None:
            return "Not initialized"
        
        try:
            #first check for reference
            if isReferenceCorrect(self) == False:
                return "Not initialized"

            #second check for size        
            if isSizeCorrect(self) == False:
                return "Not initialized or size too large to display"

            empty = ""
            if self.val['d']['size'] == 0:
                empty = "empty "

            return "%s%s<%s>" % ( empty, self.container, self.itype )
        except:
            return "Not initialized"
 
class QLinkedListPrinter:
    "Print a QLinkedList"
 
    class _iterator:
        def __init__(self, nodetype, begin, size):
            self.nodetype = nodetype
            self.it = begin
            self.pos = 0
            self.size = size
 
        def __iter__(self):
            return self
 
        def next(self):
            if self.pos >= self.size: #size will be 0 if children fail
                raise StopIteration
 
            pos = self.pos
            val = self.it['t']
            self.it = self.it['n']
            self.pos = self.pos + 1
            return ('[%d]' % pos, val)
 
    def __init__(self, val):
        try:
            self.val = val
            self.itype = self.val.type.template_argument(0)
        except:
            self.val = None
            self.itype = None
 
    def children(self):
        try:
            if self.val == None:
                return self._iterator(None, None, 0)

            #first check for reference
            if isReferenceCorrect(self) == False:
                return self._iterator(None, None, 0)

            #second check for size        
            if isSizeCorrect(self) == False:
                return self._iterator(None, None, 0)

            return self._iterator(self.itype, self.val['e']['n'], self.val['d']['size'])
        except:
            return self._iterator(None, None, 0)

    def to_string(self):
        if self.val == None:
            return "Not initialized"

        try:
            #first check for reference
            if isReferenceCorrect(self) == False:
                return "Not initialized"

            #second check for size        
            if isSizeCorrect(self) == False:
                return "Not initialized or size too large to display"

            empty = ""
            if self.val['d']['size'] == 0:
                empty = "empty "

            return "%sQLinkedList<%s>" % ( empty, self.itype )
        except:
            return "Not initialized"

class QMapPrinter:
    "Print a QMap"
 
    class _iterator:
        def __init__(self, val):
            self.val = val
            if self.val == None:
                return

            self.ktype = self.val.type.template_argument(0)
            self.vtype = self.val.type.template_argument(1)
            self.size = self.val['d'].dereference()['size']
            if self.size == 0:
                return

            self.data_node = self.val['e']['forward'][0]
            self.count = 0
 
        def __iter__(self):
            return self 
 
        def payload (self):
	    if self.val == None:
		return None

            nodeType = lookupType('QMapNode<%s, %s>' % (self.ktype, self.vtype))
            return nodeType.sizeof - 2 * lookupType("void").pointer().sizeof

        def concrete (self, data_node):
            if self.val == None:
                print "self cal in concrete in NONE"
                return None
            try:
                node_type = lookupType('QMapNode<%s, %s>' % (self.ktype, self.vtype)).pointer()
                return (data_node.cast(lookupType('char').pointer()) - self.payload()).cast(node_type)
            except:
		self.value = None
                return None

        def next(self):
            if self.val == None:
                raise StopIteration

            if self.size == 0:
                raise StopIteration

            if self.data_node == self.val['e']:
                raise StopIteration

            if self.concrete(self.data_node) == None:
                raise StopIteration

	    try:
                node = self.concrete(self.data_node).dereference()
                if self.count % 2 == 0: #we might poke to wrong memory location here, catch the exception
                    item = node['key']
                else:
                    item = node['value']
                    self.data_node = node['forward'][0]
                    
                    #TODO future work
                    #get QVariant numer identifier item['d']['type']
                    #get QVariant textual description gdb.parse_and_eval('((QVariant*)%s)->typeName()' % (item.address))
                    #this is for other kind of objects if QMap is not QVariantMap, then we can check atomic reference
                    #ref = item['d']['ref']
                    #print "---> ", ref['_q_value']                        
                    #print "----->", item['ref']['_q_value']

                result = ('[%d]' % self.count, item)
                self.count = self.count + 1
                return result 
            except:
                raise StopIteration

    def __init__(self, val, container):
        self.val = val
        try:
            if str(self.val.type.template_argument(1)) == str(lookupType('QVariant')):
                self.qvariant = True
                self.val = None
            else:
                self.qvariant = False
        except:
            self.qvariant = False

        self.container = container
 
    def children(self):
        try:
            if self.val == None:
                return self._iterator(None)

            #first check for reference
            if isReferenceCorrect(self) == False:
                return self._iterator(None)

            #second check for size        
            if isSizeCorrect(self) == False:
                return self._iterator(None)

            return self._iterator(self.val)
        except:
            return self._iterator(None)

    def to_string(self):
        if self.qvariant == True:
            return "QVariant types printing not supported"

        if self.val == None:
            return "Not initialized"
        
        try:
            #first check for reference
            if isReferenceCorrect(self) == False:
                return "Not initialized"

            #second check for size        
            if isSizeCorrect(self) == False:
                return "Not initialized or size too large to display"

            empty = ""
            if self.val['d']['size'] == 0:
                empty = "empty "

            return "%s%s<%s, %s>" % ( empty, self.container, self.val.type.template_argument(0), self.val.type.template_argument(1) )
        except:
            return "Not initialized"
 
    def display_hint (self):
        return 'map'
 
class QHashPrinter:
    "Print a QHash"
 
    class _iterator:
        def __init__(self, val):
            self.val = val
            if self.val == None:
                return
            try:
                self.d = self.val['d']
                self.ktype = self.val.type.template_argument(0)
                self.vtype = self.val.type.template_argument(1)
                self.end_node = self.d.cast(lookupType('QHashData::Node').pointer())
                self.data_node = self.firstNode()
                if self.data_node == None:
                    self.val = None

                self.count = 0
            except:
                self.val = None
                return

        def __iter__(self):
            return self
 
        def hashNode (self):
            try:
                "Casts the current QHashData::Node to a QHashNode and returns the result. See also QHash::concrete()"
                return self.data_node.cast(lookupType('QHashNode<%s, %s>' % (self.ktype, self.vtype)).pointer())
            except:
                return None

        def firstNode (self):
            try:
                "Get the first node, See QHashData::firstNode()."
                e = self.d.cast(lookupType('QHashData::Node').pointer())
                #print "QHashData::firstNode() e %s" % e
                bucketNum = 0
                bucket = self.d['buckets'][bucketNum]
                #print "QHashData::firstNode() *bucket %s" % bucket
                n = self.d['numBuckets']
                #print "QHashData::firstNode() n %s" % n
                while n:
                    #print "QHashData::firstNode() in while, n %s" % n;
                    if bucket != e:
                        #print "QHashData::firstNode() in while, return *bucket %s" % bucket
                        return bucket
                    bucketNum += 1
                    bucket = self.d['buckets'][bucketNum]
                    #print "QHashData::firstNode() in while, new bucket %s" % bucket
                    n -= 1
                #print "QHashData::firstNode() return e %s" % e
                return e
            except:
                return None

        def nextNode (self, node):
            try:
                "Get the nextNode after the current, see also QHashData::nextNode()."
                #print "******************************** nextNode"
                #print "nextNode: node %s" % node
                next = node['next'].cast(lookupType('QHashData::Node').pointer())
                e = next

                #print "nextNode: next %s" % next
                if next['next']:
                    #print "nextNode: return next"
                    return next

                #print "nextNode: node->h %s" % node['h']
                #print "nextNode: numBuckets %s" % self.d['numBuckets']
                start = (node['h'] % self.d['numBuckets']) + 1
                bucketNum = start
                #print "nextNode: start %s" % start
                bucket = self.d['buckets'][start]
                #print "nextNode: bucket %s" % bucket
                n = self.d['numBuckets'] - start
                #print "nextNode: n %s" % n
                while n:
                    #print "nextNode: in while; n %s" % n
                    #print "nextNode: in while; e %s" % e
                    #print "nextNode: in while; *bucket %s" % bucket
                    if bucket != e:
                        #print "nextNode: in while; return bucket %s" % bucket
                        return bucket
                    bucketNum += 1
                    bucket = self.d['buckets'][bucketNum]
                    n -= 1
                #print "nextNode: return e %s" % e
                return e
            except:
                return None
 
        def next(self):
            if self.val == None:
                raise StopIteration

            "GDB iteration, first call returns key, second value and then jumps to the next hash node."
            if self.data_node == self.end_node:
                raise StopIteration
 
            node = self.hashNode()
            if node == None:
                raise StopIteration
                
            if self.count % 2 == 0:
                item = node['key']
            else:
                item = node['value']
                self.data_node = self.nextNode(self.data_node)
                
            if self.data_node == None:
                raise StopIteration
                
            self.count = self.count + 1
            return ('[%d]' % self.count, item)
 
    def __init__(self, val, container):
        self.val = val
        try:
            if str(self.val.type.template_argument(1)) == str(lookupType('QVariant')):
                self.qvariant = True
                self.val = None
            else:
                self.qvariant = False
        except:
            self.qvariant = False

        self.container = container
 
    def children(self):
        try:
            if self.val == None:
                return self._iterator(None)

            #first check for reference
            if isReferenceCorrect(self) == False:
                return self._iterator(None)

            #second check for size        
            if isSizeCorrect(self) == False:
                return self._iterator(None)
    
            return self._iterator(self.val)
        except:
            return self._iterator(None)
 
    def to_string(self):
        if self.qvariant == True:
            return "QVariant types printing not supported"

        if self.val == None:
            return "Not initialized"
        
        try:
            #first check for reference
            if isReferenceCorrect(self) == False:
                return "Not initialized"

            #second check for size        
            if isSizeCorrect(self) == False:
                return "Not initialized or size too large to display"

            empty = ""
            if self.val['d']['size'] == 0:
                empty = "empty "
 
            return "%s%s<%s, %s>" % ( empty, self.container, self.val.type.template_argument(0), self.val.type.template_argument(1) )
        except:
            return "Not initialized"

    def display_hint (self):
        return 'map'
 
#TODO missing good (reference) check if date is valid - failing!
class QDatePrinter:
 
    def __init__(self, val):
        self.val = val
 
    def to_string(self):
        try:
            julianDay = self.val['jd']
            if julianDay == 0 or julianDay == 0xffffffff: #-1 means NullDate ==> invalid
                return "Uninitialized or invalid QDate"

            # Copied from Qt sources
            if julianDay >= 2299161:
                # Gregorian calendar starting from October 15, 1582
                # This algorithm is from Henry F. Fliegel and Thomas C. Van Flandern
                ell = julianDay + 68569;
                n = (4 * ell) / 146097;
                ell = ell - (146097 * n + 3) / 4;
                i = (4000 * (ell + 1)) / 1461001;
                ell = ell - (1461 * i) / 4 + 31;
                j = (80 * ell) / 2447;
                d = ell - (2447 * j) / 80;
                ell = j / 11;
                m = j + 2 - (12 * ell);
                y = 100 * (n - 49) + i + ell;
            else:
                # Julian calendar until October 4, 1582
                # Algorithm from Frequently Asked Questions about Calendars by Claus Toendering
                julianDay += 32082;
                dd = (4 * julianDay + 3) / 1461;
                ee = julianDay - (1461 * dd) / 4;
                mm = ((5 * ee) + 2) / 153;
                d = ee - (153 * mm + 2) / 5 + 1;
                m = mm + 3 - 12 * (mm / 10);
                y = dd - 4800 + (mm / 10);
                if y <= 0:
                    --y;
            return "%d-%02d-%02d" % (y, m, d)
        except:
            return "Not initialized"
 
#TODO missing good (reference) check if time is valid
class QTimePrinter:
 
    def __init__(self, val):
        self.val = val
 
    def to_string(self):
        try:
            ds = self.val['mds']

            if ds == -1 or ds > 86400000: #MSECS_PER_DAY = 86400000 same condition as isvalid in QT
                return "Uninitialized or invalid QTime"

            MSECS_PER_HOUR = 3600000
            SECS_PER_MIN = 60
            MSECS_PER_MIN = 60000

            hour = ds / MSECS_PER_HOUR
            minute = (ds % MSECS_PER_HOUR) / MSECS_PER_MIN
            second = (ds / 1000)%SECS_PER_MIN
            msec = ds % 1000
            return "%02d:%02d:%02d.%03d" % (hour, minute, second, msec)
        except:
            return "Not initialized"

class QDateTimePrinter:
 
    def __init__(self, val):
        self.val = val
 
    def to_string(self):
        try:
            #first check for reference
            #val['d'] is a QDateTimePrivate, but for some reason casting to that doesn't work
            #so we are usign this little strange way to dereference the value
            reference = self.val['d'].cast(lookupType('char').pointer());
            reference = reference.cast(lookupType('QAtomicInt').pointer()).dereference();
            if reference['_q_value'] < 0 or reference['_q_value'] > REF_LIMIT:            
                return "Not initialized"

            #val['d'] is a QDateTimePrivate, but for some reason casting to that doesn't work
            #so work around by manually adjusting the pointer
            date = self.val['d'].cast(lookupType('char').pointer());
            date += lookupType('int').sizeof #increment for QAtomicInt ref;
            date = date.cast(lookupType('QDate').pointer()).dereference();

            time = self.val['d'].cast(lookupType('char').pointer());
            time += lookupType('int').sizeof + lookupType('QDate').sizeof #increment for QAtomicInt ref; and QDate date;
            time = time.cast(lookupType('QTime').pointer()).dereference();
            return "%s %s" % (date, time)
        except:
            return "Not initialized"
 
class QUrlPrinter:
 
    def __init__(self, val):
        self.val = val
 
    def to_string(self):
        try:
            if isReferenceCorrect(self) == False:
                return "Not initialized"

            return self.val['d']['encodedOriginal']
        except RuntimeError, error:
            try:
                #if no debug information is avaliable for Qt, try guessing the correct address for encodedOriginal
                #problem with this is that if QUrlPrivate members get changed, this fails
                offset = lookupType('int').sizeof
                offset += offset % lookupType('void').pointer().sizeof #alignment
                offset += lookupType('QString').sizeof * 6
                offset += lookupType('QByteArray').sizeof
                encodedOriginal = self.val['d'].cast(lookupType('char').pointer());
                encodedOriginal += offset
                encodedOriginal = encodedOriginal.cast(lookupType('QByteArray').pointer()).dereference();
                encodedOriginal = encodedOriginal['d']['data'].string()
                return encodedOriginal
            except:
                return "Not initialized"
        except:
            return "Not initialized"
 
class QSetPrinter:
    "Print a QSet"
 
    def __init__(self, val):
        self.val = val
 
    class _iterator:
        def __init__(self, hashIterator):
            self.hashIterator = hashIterator
            self.count = 0
 
        def __iter__(self):
            return self
 
        def next(self):
            if self.hashIterator == None:
                raise StopIteration

            if self.hashIterator.data_node == self.hashIterator.end_node:
                raise StopIteration
 
            node = self.hashIterator.hashNode()
 
            item = node['key']
            self.hashIterator.data_node = self.hashIterator.nextNode(self.hashIterator.data_node)
 
            self.count = self.count + 1
            return ('[%d]' % (self.count-1), item)
 
    def children(self):
        try:
            #first check for reference
            ref = self.val['q_hash']['d']['ref'] 
            if ref['_q_value'] < 0 or ref['_q_value'] > REF_LIMIT:            
                return self._iterator(None)

            #second check for size        
            if self.val['q_hash']['d']['size'] > SIZE_LIMIT:
                return self._iterator(None)

            hashPrinter = QHashPrinter(self.val['q_hash'], None)
            hashIterator = hashPrinter._iterator(self.val['q_hash'])
            return self._iterator(hashIterator)
        except:
            return self._iterator(None)
 
    def to_string(self):
        if self.val == None:
            return "Not initialized"
        
        try:
            #first check for reference
            ref = self.val['q_hash']['d']['ref']
            if ref['_q_value'] < 0 or ref['_q_value'] > REF_LIMIT:            
                return "Not initialized"

            #second check for size        
            if self.val['q_hash']['d']['size'] > SIZE_LIMIT:
                return "Not initialized or size too large to display"
                
            empty = ""
            if self.val['q_hash']['d']['size'] == 0:
                empty = "empty " #just add "<space>"
               
 
            return "%sQSet<%s>" % ( empty , self.val.type.template_argument(0) )
        except:
            return "Not initialized"


#TODO how to make this one safe, it is failing!?
class QCharPrinter:
 
    def __init__(self, val):
        self.val = val
 
    def to_string(self):
        try:
            return unichr(self.val['ucs']).encode('utf-8')
        except:
            return "Not initialized"

    def display_hint (self):
        return 'string'
 
def register_qt4_printers (obj):
    if obj == None:
        obj = gdb
 
    obj.pretty_printers.append (lookup_function)
 
def lookup_function (val):
    "Look-up and return a pretty-printer that can print val."
 
    # Get the type.
    type = val.type;
 
    # If it points to a reference, get the reference.
    if type.code == gdb.TYPE_CODE_REF:
        type = type.target ()
 
    # Get the unqualified type, stripped of typedefs.
    type = type.unqualified ().strip_typedefs ()
 
    # Get the type name.
    typename = type.tag
    if typename == None:
        return None
 
    # Iterate over local dictionary of types to determine
    # if a printer is registered for that type.  Return an
    # instantiation of the printer if found.
    for function in pretty_printers_dict:
        if function.search (typename):
            return pretty_printers_dict[function] (val)
 
    # Cannot find a pretty printer.  Return None.
    return None

#check for reference to object (test value of QAtomicInt) stored in d.ref._q_value
#if this number is less than 0 then it is invalid, if the number is higher than 512 it is really suspicious
def isReferenceCorrect(object):
    #first check for reference
    ref = object.val['d']['ref'] 
    if ref['_q_value'] < 0 or ref['_q_value'] > REF_LIMIT:            
        return False
    else:
        return True

#check for size (number of elements) of object  stored in d.size
#if this number is less than 0 then it is invalid, if the number is higher than 512 then we are unable to display it - without performance issues (it still can be invalid)
def isSizeCorrect(object):
    #second check for size        
    if object.val['d']['size'] < 0  or object.val['d']['size'] > SIZE_LIMIT:
        return False
    else:
        return True

typeCache = {}

def lookupType(typestring):
    type = typeCache.get(typestring)
    #warn("LOOKUP 1: %s -> %s" % (typestring, type))
    if not type is None:
        return type

    if typestring == "void":
        type = gdb.lookup_type(typestring)
        typeCache[typestring] = type
        return type

    if typestring.find("(anon") != -1:
        # gdb doesn't like
        # '(anonymous namespace)::AddAnalysisMessageSuppressionComment'
        typeCache[typestring] = None
        return None

    try:
        type = gdb.parse_and_eval("{%s}&main" % typestring).type
        typeCache[typestring] = type
        return type
    except:
        pass


def build_dictionary ():
    pretty_printers_dict[re.compile('^QString$')] = lambda val: QStringPrinter(val)
    pretty_printers_dict[re.compile('^QByteArray$')] = lambda val: QByteArrayPrinter(val)
    pretty_printers_dict[re.compile('^QList<.*>$')] = lambda val: QListPrinter(val, 'QList', None)
    pretty_printers_dict[re.compile('^QStringList$')] = lambda val: QListPrinter(val, 'QStringList', 'QString')
    pretty_printers_dict[re.compile('^QQueue')] = lambda val: QListPrinter(val, 'QQueue', None)
    pretty_printers_dict[re.compile('^QVector<.*>$')] = lambda val: QVectorPrinter(val, 'QVector')
    pretty_printers_dict[re.compile('^QStack<.*>$')] = lambda val: QVectorPrinter(val, 'QStack')
    pretty_printers_dict[re.compile('^QLinkedList<.*>$')] = lambda val: QLinkedListPrinter(val)
    pretty_printers_dict[re.compile('^QMap<.*>$')] = lambda val: QMapPrinter(val, 'QMap')
    pretty_printers_dict[re.compile('^QMultiMap<.*>$')] = lambda val: QMapPrinter(val, 'QMultiMap')
    pretty_printers_dict[re.compile('^QHash<.*>$')] = lambda val: QHashPrinter(val, 'QHash')
    pretty_printers_dict[re.compile('^QMultiHash<.*>$')] = lambda val: QHashPrinter(val, 'QMultiHash')
    pretty_printers_dict[re.compile('^QDate$')] = lambda val: QDatePrinter(val)
    pretty_printers_dict[re.compile('^QTime$')] = lambda val: QTimePrinter(val)
    pretty_printers_dict[re.compile('^QDateTime$')] = lambda val: QDateTimePrinter(val)
    pretty_printers_dict[re.compile('^QUrl$')] = lambda val: QUrlPrinter(val)
    pretty_printers_dict[re.compile('^QSet<.*>$')] = lambda val: QSetPrinter(val)
    pretty_printers_dict[re.compile('^QChar$')] = lambda val: QCharPrinter(val)
 
 
pretty_printers_dict = {}
 
build_dictionary ()

register_qt4_printers (None)
