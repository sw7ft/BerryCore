/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_listitemtypemapper_h
#define cascades_listitemtypemapper_h

#include <QVariant>
#include <QtDeclarative/QtDeclarative>

#include <bb/cascades/bbcascades_global.h>


namespace bb {
namespace cascades {
    /*!
     * @brief An interface for determining the type of each item in a @c ListView.
     *
     * An object implementing @c %ListItemTypeMapper can optionally be provided to a @c %ListView.
     * In this case, the @c %ListView will call @c %ListItemTypeMapper::itemType()
     * instead of calling @c %DataModel::itemType() when the @c %ListView needs to know the type
     * of an item.
     *
     * You can apply a @c %ListItemTypeMapper to a ListView using @c ListView::setListItemTypeMapper().
     *
     * @xmlonly
     * <apigrouping group="User interface/List"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT ListItemTypeMapper
    {

    public:
        /*!
         * @brief Destructs this @c %ListItemTypeMapper.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~ListItemTypeMapper();

        /*!
         * @brief Returns the item type based on the data that's contained in the specified
         * list item.
         * 
         * This function is called by @c ListView for each item it loads.
         *
         * @param data The value returned by @c DataModel::data() for the specified item.
         * @param indexPath An index path specifying the item whose type is requested.
         * 
         * @return The item type based on values in the given item.
         *
         * @since BlackBerry 10.0.0
         */
        virtual QString itemType(const QVariant& data, const QVariantList& indexPath) = 0;
    };
}
}
Q_DECLARE_INTERFACE(bb::cascades::ListItemTypeMapper, "com.blackberry.cascades.ListItemTypeMapper")

#endif // cascades_listitemtypemapper_h
