/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_resource_h
#define cascades_resource_h


#include <bb/cascades/bbcascades_global.h>
#include <QtDeclarative/QtDeclarative>

namespace bb {
    namespace cascades {

        class ResourcePrivate;

        /*!
         * 
         * @brief Abstract base class inherited by all resources.
         *
         * A resource is content that is usually provided at runtime or is generated dynamically, as opposed to 
         * assets which are usually packaged with the application. Resources can therefore
         * be slower to load and might even fail to load in some situations (for example, with corrupt data or a bad network 
         * connection).
         *
         * All resources go through several states during loading. To 
         * listen to the state changes and get other data from the resource, a 
         * ResourceTracker must be used (for example, an ImageTracker is used when listening for state 
         * changes on an Image). The ResourceTracker encapsulates the asynchronous behavior of a 
         * resource by providing means to receive signals and access resource data and states. 
         * 
         * Resources are value objects that use implicit data sharing, which allow them to be 
         * passed around as values.
         *
         * @xmlonly
         * <apigrouping group="User interface/Resources"/>
         * @endxmlonly
         *
         * @since BlackBerry 10.0.0
         */
        class BBCASCADES_EXPORT Resource {
        public:
            virtual ~Resource();

            /*!
              * @brief Returns true if the resource is null.
              *
              * @return @c true if this resource is null, @c false otherwise.
             *
             * @since BlackBerry 10.0.0
              */
            bool isNull() const;

        protected:
            /*! @cond PRIVATE */
            Resource(ResourcePrivate *_d_ptr);
            ResourcePrivate * const d_ptr;
            /*! @endcond */

        private:
            /*! @cond PRIVATE */
            Q_DECLARE_PRIVATE(Resource)
            /*! @endcond */
        };
        
  }
}

#endif	/* cascades_resource_h */
