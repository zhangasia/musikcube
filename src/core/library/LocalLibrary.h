//////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2007-2016 musikcube team
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the name of the author nor the names of other contributors may
//      be used to endorse or promote products derived from this software
//      without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include <core/config.h>
#include <core/db/Connection.h>

#include <core/library/ILibrary.h>
#include <core/library/IIndexer.h>
#include <core/library/IQuery.h>
#include <core/library/query/local/LocalQueryBase.h>

#include <thread>
#include <mutex>
#include <condition_variable>

#include <boost/utility.hpp>
#include <sigslot/sigslot.h>
#include <string>

namespace musik { namespace core { namespace library {

    class LocalLibrary :
        public ILibrary,
        public musik::core::runtime::IMessageTarget,
        public std::enable_shared_from_this<LocalLibrary>,
        boost::noncopyable
    {
        public:
            using IQueryPtr = std::shared_ptr<musik::core::db::IQuery>;
            using LocalQuery = musik::core::db::LocalQueryBase;
            using LocalQueryPtr = std::shared_ptr<LocalQuery>;

            static ILibraryPtr Create(std::string name, int id);

            virtual ~LocalLibrary();

            /* ILibrary */
            virtual int Enqueue(IQueryPtr query, unsigned int options = 0);

            virtual musik::core::IIndexer *Indexer();
            virtual int Id();
            virtual const std::string& Name();
            virtual void SetMessageQueue(musik::core::runtime::IMessageQueue& queue);
            virtual void Close();

            /* IMessageTarget */
            virtual void ProcessMessage(musik::core::runtime::IMessage &message);

            /* implementation specific */
            std::string GetLibraryDirectory();
            std::string GetDatabaseFilename();
            static void CreateDatabase(db::Connection &db);

        private:
            typedef std::list<LocalQueryPtr> QueryList;

            LocalLibrary(std::string name, int id); /* ctor */

            void RunQuery(LocalQueryPtr query, bool notify = true);
            virtual void Exit();
            bool Exited();
            void ThreadProc();
            LocalQueryPtr GetNextQuery();

            QueryList queryQueue;

            musik::core::runtime::IMessageQueue* messageQueue;

            std::string identifier;
            int id;
            std::string name;
            bool exit;

            std::thread* thread;
            std::condition_variable queueCondition;
            std::mutex mutex;

            core::IIndexer *indexer;
            core::db::Connection db;
    };

} } }
