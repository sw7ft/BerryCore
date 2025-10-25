/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_NOTEBOOK_NOTEBOOKSERVICERESULT_HPP
#define BB_PIM_NOTEBOOK_NOTEBOOKSERVICERESULT_HPP

#include <bb/pim/Global>

namespace bb
{
namespace pim
{
namespace notebook
{

/*!
 * @headerfile NotebookServiceResult.hpp <bb/pim/notebook/NotebookServiceResult>
 *
 * @brief The @c NotebookServiceResult class provides status codes that are returned from add, update, and delete
 * functions in @c NotebookService.
 *
 * @details After invoking an add, update, or delete function in the @c %NotebookService class, you should first
 * compare its status code to @c NotebookServiceResult::Success to determine whether it succeeded (in which case the
 * appropriate signal will be emitted).  If the function did not succeed, you can determine the granularity
 * of the error-handling that you want to perform by comparing against the possible error statuses documented in the
 * function being invoked.
 *
 * @see NotebookService
 *
 * @xmlonly
 * <apigrouping group="App Integration/Notebook"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT NotebookServiceResult
{
public:
    /*!
     * @brief An enumeration of possible status codes from add, update, and delete @c NotebookService functions.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * Indicates that the function completed successfully.
         *
         * @since BlackBerry 10.0.0
         */
        Success = 0,

        /*!
         * Indicates that the function failed due to an unknown reason.
         *
         * @since BlackBerry 10.0.0
         */
        InternalError = 1,

        /*!
         * Indicates that the function failed because a non-existent or inaccessible account was specified.
         *
         * @since BlackBerry 10.0.0
         */
        InaccessibleAccount = 2,

        /*!
         * Indicates that the function failed because a non-existent @c Notebook was specified.
         *
         * @since BlackBerry 10.0.0
         */
        NonExistentNotebook = 3,

        /*!
         * Indicates that the function failed because a non-existent @c NotebookEntry was specified.
         *
         * @since BlackBerry 10.0.0
         */
        NonExistentNotebookEntry = 4,

        /*!
         * Indicates that the function failed because a @c %NotebookEntry was moved to a disallowed parent @c %Notebook.
         *
         * @since BlackBerry 10.0.0
         */
        ParentNotebookNotAllowed = 5,

        /*!
         * Indicates that the function failed because the requested notebook or notebook entry operation is not allowed.
         *
         * @since BlackBerry 10.0.0
         */
        OperationNotAllowed = 6,

        /*!
         * Indicates that the function failed because the domain is hard locked and the enterprise file system is currently not readable.
         *
         * @since BlackBerry 10.3.0
         */
        DomainLockedError = 7,

        /*!
         * Indicates that the function failed because a @c %Notebook was added to an account that does not support that kind of @c Notebook.
         *
         * @since BlackBerry 10.3.0
         */
        NotebookNotSupported = 8,
    };

private:
    NotebookServiceResult();
    ~NotebookServiceResult();
};

} // namespace notebook
} // namespace pim
} // namespace bb

#endif /* BB_PIM_NOTEBOOK_NOTEBOOKSERVICERESULT_HPP */
