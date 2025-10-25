/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_datamodelchangetype_h
#define cascades_datamodelchangetype_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
namespace cascades {

/*!
 *
 * @brief Represents different types of data model changes.
 *
 * These types of data model changes are used by the @c DataModel::itemsChanged() signal,
 * and can be seen as a hint to the listener about how to visualize the model change (for
 * example, what animations, if any, to use).
 *
 * @xmlonly
 * <apigrouping group="Data management/Data models"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT DataModelChangeType {
    Q_GADGET
    Q_ENUMS (Type)
public:
    /*!
     * @brief Data model change types
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Indicates that all items might have been removed from the @c DataModel.
         *
         * This causes any @c ListView to unload all of its items, and then start
         * loading items again from the first item in the @c %DataModel.
         *
         * @since BlackBerry 10.0.0
         */
        Init,
        /*!
         * @brief Specifies that items in the @c ListView cache will remain there unless they were
         * removed from the @c DataModel.
         *
         * Must be combined with a @c DataModel::IndexMapper so that the @c %ListView
         * can determine which items it can keep in its cache. Otherwise this option
         * is treated just like @c Init.
         *
         * This option can for example be used when a batch of items have been
         * added to or removed from a @c %DataModel.
         *
         * @since BlackBerry 10.0.0
         */
        AddRemove,
        /*!
         * @brief Specifies that no items have been added or removed, but the
         * @c ListView needs to call @c DataModel::data() again for all cached items.
         *
         * This option can for example be used when all strings in the application
         * must be reloaded due to a change of locale.
         *
         * @since BlackBerry 10.0.0
         */
        Update
    };

private:
    DataModelChangeType();
    ~DataModelChangeType();
};

}
}

#endif // cascades_datamodelchangetype_h

