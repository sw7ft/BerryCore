/* Copyright (C) 2011-2013-2013-2013-2013 Research In Motion Limited.  */

#ifndef cascades_qlistdatamodel_h
#define cascades_qlistdatamodel_h

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QSharedDataPointer>
#include <QtCore/QSharedPointer>
#include <QtCore/QVariant>
#include <bb/cascades/bbcascades_global.h>

#include <bb/cascades/databinding/datamodel.h>
#include <bb/cascades/databinding/arraydatamodel.h>


namespace bb {
namespace cascades {

   /*!
    * @brief Contains a list of \<Item\> values, typically for a @c ListView.
    *
    * The templated @c %QListDataModel Model class implements the
    * abstract @c DataModel class.
    *
    * Template class \<Item\> must be convertible to @c QVariant in
    * order for the @c data() function to work. To accomplish that, use the
    * @c Q_DECLARE_METATYPE macro. For example:
    *
    * @code
    * namespace mynamespace {
    * class Contact {
    * ...
    * }
    * } // mynamespace
    * Q_DECLARE_METATYPE( mynamespace::Contact *);
    * @endcode
    *
    * Then the custom object (pointer to Contact) would become convertible to and from
    * @c QVariant:
    *
    * @code
    * Contact *pCnt1 = new Contact();
    * QVariant q = QVariant::fromValue(pCnt1);
    * Contact *pCnt2 = q.value<Contact*>();
    * @endcode
    *
    * And usable in the model: QListDataModel<Contact *> contactsModel;
    *
    * Similarly, Contacts objects (not pointers) can be declared and stored in the model.
    *
    * As a convenience, @c %QListDataModel includes the following typedefs: @c QVariantListDataModel,
    * @c QStringListDataModel, and @c QMapListDataModel. For more information about these typedefs, see
    * <a href="/native/reference/cascades/bb__cascades.html">bb::cascades</a>.
    * 
    * @see ListView, DataModel
    *
    * @xmlonly
    * <apigrouping group="Data management/Data models"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    template <class Item>
    class QListDataModel : public DataModel {
    public:

        /*!
         * @brief Constructs an empty @c %QListDataModel.
         *
         * @since BlackBerry 10.0.0
         */
        QListDataModel() : mArrayDataModel(0) {
            initSignals();
        }

        /*!
         * @brief Constructs a @c %QListDataModel holding the provided
         * @c QVariantList.
         *
         * Ownership of the specified @c %QVariantList is transferred to this
         * @c %QListDataModel.
         *
         * @param other The initial data to be used by this @c %QListDataModel.
         *
         * @since BlackBerry 10.0.0
         */
        QListDataModel(const QList<Item> &other)  {
            initSignals();
            // Create a temporary QVariantList
            QVariantList tmp;
            tmp.reserve(other.size());
            for (int i = 0; i < other.size(); i++){
                // Convert Item to QVariant
                tmp.append(QVariant::fromValue(other.value(i)));
            }
            mArrayDataModel.append(tmp);
        }

        virtual ~QListDataModel() {}

        /*!
         * @copydoc DataModel::childCount(const QVariantList &)
         *
         * @since BlackBerry 10.0.0
         */
        virtual int childCount(const QVariantList &indexPath)
        {
            return mArrayDataModel.childCount(indexPath);
        }

        /*!
         * @copydoc DataModel::hasChildren(const QVariantList &)
         *
         * @since BlackBerry 10.0.0
         */
        virtual bool hasChildren(const QVariantList &indexPath)
        {
            return mArrayDataModel.hasChildren(indexPath);
        }

        /*!
         * @copydoc DataModel::itemType(const QVariantList &)
         *
         * @since BlackBerry 10.0.0
         */
        virtual QString itemType(const QVariantList &indexPath)
        {
            if (indexPath.length() == 1) {
                return QString();
            } else {
                return QString::null;
            }
        }

        /*!
         * @copydoc DataModel::data(const QVariantList &)
         *
         * @since BlackBerry 10.0.0
         */
        virtual QVariant data(const QVariantList &indexPath)
        {
            return mArrayDataModel.data(indexPath);
        }

        /*!
         * @brief Inserts the specified value at the end of this model.
         * The value must be convertible to a @c QVariant.
         *
         * @param value The value to be appended. Ownership of @c QObject
         *              items that don't have parents is transferred to this
         *              @c %QListDataModel.
         *
         * @since BlackBerry 10.0.0
         */
        void append(const Item &value)
        {
            mArrayDataModel.append(QVariant::fromValue(value));
        }

        /*!
         * @brief Inserts the specified list of values at the end of this
         * @c %QListDataModel.
         *
         * Each Item in the list must be convertible to a @c QVariant.
         *
         * @param values The list of @c %QVariant items to be appended.
         *               Ownership of @c QObject items that don't have
         *               parents is transferred to this @c %QListDataModel.
         *
         * @since BlackBerry 10.0.0
         */
        void append(const QList<Item> &values)
        {
            QVariantList tmp;
            tmp.reserve(values.size());
            for (int i = 0; i < values.size(); i++){
                // Convert Item to QVariant
                tmp.append(QVariant::fromValue(values.value(i)));
            }
            mArrayDataModel.append(tmp);
        }

        /*!
         * @brief Removes all values from this model. QObjects owned by this model
         * are deleted.
         *
         * @since BlackBerry 10.0.0
         */
        void clear()
        {
            mArrayDataModel.clear();
        }

        /*!
         * @brief Searches this @c QListDataModel from the specified index position
         * from until the specified item is found.
         *
         * If no such item is found, -1 is returned.
         *
         * @param value The @c QVariant to search for.
         * @param from The index position to search from.
         *
         * @return The index position if a matching item was found, -1 otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        int indexOf(const Item &value, int from = 0) const
        {
            int index = -1;
            for( int i = from ; i < size() ; i++ ){
              if( value == this->value(i) ){
                index = i;
                break;
              }
            }
            return index;
        }

        /*!
         * @brief Inserts a single @c QVariant value at the specified index
         * position @c i in this @c QListDataModel.
         *
         * If @c i is 0, the value is prepended to the list. If @c i is @c size(), the
         * value is appended to the list.
         *
         * @param i The position in this @c %QListDataModel to add the value.
         * @param value The @c %QVariant value to be inserted. Ownership of @c QObject
         *              items that don't have parents is transferred to this
         *              @c %QListDataModel.
         *
         * @since BlackBerry 10.0.0
         */
        void insert(int i, const Item &value)
        {
            mArrayDataModel.insert(i, QVariant::fromValue(value));
        }


        /*!
         * @brief Inserts a list of @c QVariant values at the specified index
         * position @c i in this @c QListDataModel.
         *
         * If @c i is 0, the values are prepended to the list. If @c i is @c size(), the
         * values are appended to the list.
         *
         * @param i The position in this @c %QListDataModel to add the list of values.
         * @param values The list of @c %QVariant items to be inserted. Ownership
         *               of @c QObject items that don't have parents is transferred
         *               to this @c %QListDataModel.
         *
         * @since BlackBerry 10.0.0
         */
        void insert(int i, const QList<Item> &values)
        {
            int valueCount = values.size();
            if (i >= 0 && i <= mArrayDataModel.size() && valueCount > 0) {
                QVariantList tmp;
                tmp.reserve(values.size());
                for (int j = 0; j < values.size(); j++){
                    // Convert Item to QVariant
                    tmp.append(QVariant::fromValue(values.value(j)));
                }
                mArrayDataModel.insert(i, tmp);
            }
        }

        /*!
         * @brief Indicates whether this @c QListDataModel is empty.
         *
         * @return @c true if the model holds no values, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        bool isEmpty() const
        {
            return mArrayDataModel.isEmpty();
        }

        /*!
         * @brief Moves the value at index position from to index position to.
         * This assumes that both from and to are at least 0 and less
         * than size().
         *
         * @param from Index position to move from.
         * @param to Index position to move to.
         *
         * @since BlackBerry 10.0.0
         */
        void move(int from, int to)
        {
            mArrayDataModel.move(from, to);
        }

        /*!
         * @brief Removes the value at index position i.
         *
         * i must be at least 0 and less than size(). QObjects owned by the model are deleted.
         *
         * @param i Index of value to be removed.
         *
         * @since BlackBerry 10.0.0
         */
        void removeAt(int i)
        {
            mArrayDataModel.removeAt(i);
        }

        /*!
         * @brief Replaces the value at index position i with value. If the old value is owned
         * by QListDataModel, it will be deleted.
         *
         * i must be at least 0 and less than size().
         *
         * @param i Index of value to be replaced.
         * @param value Replacement value. Ownership of parentless QObjects
         *              is transferred to QListDataModel.
         *
         * @since BlackBerry 10.0.0
         */
        void replace(int i, const Item &value)
        {
            mArrayDataModel.replace(i, QVariant::fromValue(value));
        }

        /*!
         * @brief Returns the number of values in the QListDataModel.
         *
         * @return Number of values in the QListDataModel.
         *
         * @since BlackBerry 10.0.0
         */
        int size() const
        {
            return mArrayDataModel.size();
        }

        /*!
        * @brief Exchange the value at index position i with the value at index
        * position j.
        *
        * The function assumes that both i and j are at least
        * 0 and less than size().
        *
        * @param i Index of first value.
        * @param j Index of second value.
         *
         * @since BlackBerry 10.0.0
        */
        void swap(int i, int j)
        {
            mArrayDataModel.swap(i, j);
        }

        /*!
        * @brief Returns the value at index position i in the QListIndexModel.
        *
        * If index i is out of bounds, the function returns a default-constructed
        * value.
        *
        * @param i Index of value to be returned.
        * @return Value at index position i.
         *
         * @since BlackBerry 10.0.0
        */
        Item value(int i) const
        {
            return mArrayDataModel.value(i).template value<Item>();
        }

        /*!
        * @brief Returns the value at index position i in the QListIndexModel.
        *
        * If index i is not at least 0 and less than size(), the function returns defaultValue.
        *
        * @param i Index of value to be returned.
        * @param defaultValue Value to be returned if i is out of bounds.
        * @return Value at index position i.
         *
         * @since BlackBerry 10.0.0
        */
        Item value(int i, const Item &defaultValue) const
        {
            return mArrayDataModel.value(i, QVariant::fromValue(defaultValue)).template value<Item>();
        }

        /*!
        * @brief Appends the specified value to the @c %QListDataModel and returns a reference
        * to the @c %QListDataModel.
        *
        * @param value The value to be appended. Ownership of @c QObject items that don't
        *              have parents is transferred to this @c %QListDataModel.
        *
        * @return A reference to the @c %QListDataModel.
         *
         * @since BlackBerry 10.0.0
        */
        QListDataModel &operator<<(const Item & value)
        {
            mArrayDataModel.append(QVariant::fromValue(value));
            return *this;
        }

    private:
        /*! @cond PRIVATE
         *
         * @since BlackBerry 10.0.0
         */
        void initSignals() {
            QObject::connect(&mArrayDataModel, SIGNAL(itemAdded(QVariantList)),
                             this, SIGNAL(itemAdded(QVariantList)));

            QObject::connect(&mArrayDataModel, SIGNAL(itemUpdated(QVariantList)),
                             this, SIGNAL(itemUpdated(QVariantList)));

            QObject::connect(&mArrayDataModel, SIGNAL(itemRemoved(QVariantList)),
                             this, SIGNAL(itemRemoved(QVariantList)));

            QObject::connect(&mArrayDataModel, SIGNAL(itemMoved(QVariantList,QVariantList)),
                             this, SIGNAL(itemMoved(QVariantList,QVariantList)));

            QObject::connect(&mArrayDataModel,
                             SIGNAL(itemsChanged(bb::cascades::DataModelChangeType::Type,QSharedPointer<bb::cascades::DataModel::IndexMapper>)),
                             this,
                             SIGNAL(itemsChanged(bb::cascades::DataModelChangeType::Type,QSharedPointer<bb::cascades::DataModel::IndexMapper>)));
        }


        ArrayDataModel mArrayDataModel;
        Q_DISABLE_COPY(QListDataModel)
        /*! @endcond */
    };


    /*!
    * @brief The QVariantListDataModel is a shortcut for QListDataModel<QVariant>
    *
    * @relates QListDataModel
    *
    * @since BlackBerry 10.0.0
    */
    typedef QListDataModel<QVariant> QVariantListDataModel;

    /*!
    * @brief The QStringListDataModel is a shortcut for QListDataModel<QString>
    *
    * @relates QListDataModel
    *
    * @since BlackBerry 10.0.0
    */
    typedef QListDataModel<QString> QStringListDataModel;

    /*!
    * @brief The QMapListDataModel is a shortcut for QListDataModel<QVariantMap>
    *
    * @relates QListDataModel
    *
    * @since BlackBerry 10.0.0
    */
    typedef QListDataModel<QVariantMap> QMapListDataModel;

}
}

#endif // cascades_arraydatamodel_h
