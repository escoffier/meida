// **********************************************************************
//
// Copyright (c) 2003-2016 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************
//
// Ice version 3.6.3
//
// <auto-generated>
//
// Generated from file `stream.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#ifndef __E__workspace_DTNVS3000_meida_mediaclinet_generated_stream_h__
#define __E__workspace_DTNVS3000_meida_mediaclinet_generated_stream_h__

#include <IceUtil/PushDisableWarnings.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/StreamHelpers.h>
#include <Ice/Proxy.h>
#include <Ice/GCObject.h>
#include <Ice/AsyncResult.h>
#include <Ice/Incoming.h>
#include <Ice/IncomingAsync.h>
#include <Ice/FactoryTableInit.h>
#include <IceUtil/ScopedArray.h>
#include <IceUtil/Optional.h>
#include <Ice/StreamF.h>
#include <IceUtil/UndefSysMacros.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 306
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 3
#       error Ice patch level mismatch!
#   endif
#endif

namespace IceProxy
{

namespace Media
{

class Stream;
void __read(::IceInternal::BasicStream*, ::IceInternal::ProxyHandle< ::IceProxy::Media::Stream>&);
::IceProxy::Ice::Object* upCast(::IceProxy::Media::Stream*);

}

}

namespace Media
{

class Stream;
::Ice::Object* upCast(::Media::Stream*);
typedef ::IceInternal::Handle< ::Media::Stream> StreamPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Media::Stream> StreamPrx;
void __patch(StreamPtr&, const ::Ice::ObjectPtr&);

}

namespace Media
{

class RequestCanceledException : public ::Ice::UserException
{
public:

    RequestCanceledException() {}
    virtual ~RequestCanceledException() throw();

    virtual ::std::string ice_name() const;
    virtual RequestCanceledException* ice_clone() const;
    virtual void ice_throw() const;

protected:
    virtual void __writeImpl(::IceInternal::BasicStream*) const;
    virtual void __readImpl(::IceInternal::BasicStream*);
    using ::Ice::UserException::__writeImpl;
    using ::Ice::UserException::__readImpl;
};

static RequestCanceledException __RequestCanceledException_init;

struct RealStreamRespParam
{
    ::std::string id;
    ::std::string callid;
    ::std::string sourceip;
    ::std::string sourceport;

    bool operator==(const RealStreamRespParam& __rhs) const
    {
        if(this == &__rhs)
        {
            return true;
        }
        if(id != __rhs.id)
        {
            return false;
        }
        if(callid != __rhs.callid)
        {
            return false;
        }
        if(sourceip != __rhs.sourceip)
        {
            return false;
        }
        if(sourceport != __rhs.sourceport)
        {
            return false;
        }
        return true;
    }

    bool operator<(const RealStreamRespParam& __rhs) const
    {
        if(this == &__rhs)
        {
            return false;
        }
        if(id < __rhs.id)
        {
            return true;
        }
        else if(__rhs.id < id)
        {
            return false;
        }
        if(callid < __rhs.callid)
        {
            return true;
        }
        else if(__rhs.callid < callid)
        {
            return false;
        }
        if(sourceip < __rhs.sourceip)
        {
            return true;
        }
        else if(__rhs.sourceip < sourceip)
        {
            return false;
        }
        if(sourceport < __rhs.sourceport)
        {
            return true;
        }
        else if(__rhs.sourceport < sourceport)
        {
            return false;
        }
        return false;
    }

    bool operator!=(const RealStreamRespParam& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const RealStreamRespParam& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const RealStreamRespParam& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const RealStreamRespParam& __rhs) const
    {
        return !operator<(__rhs);
    }
};

struct RealStreamReqParam
{
    ::std::string id;
    ::std::string callid;
    ::std::string ip;
    ::Ice::Int port;
    ::std::string name;
    ::std::string pwd;
    ::std::string destip;
    ::Ice::Int destport;
    ::Ice::Int ssrc;
    ::std::string sdk;

    bool operator==(const RealStreamReqParam& __rhs) const
    {
        if(this == &__rhs)
        {
            return true;
        }
        if(id != __rhs.id)
        {
            return false;
        }
        if(callid != __rhs.callid)
        {
            return false;
        }
        if(ip != __rhs.ip)
        {
            return false;
        }
        if(port != __rhs.port)
        {
            return false;
        }
        if(name != __rhs.name)
        {
            return false;
        }
        if(pwd != __rhs.pwd)
        {
            return false;
        }
        if(destip != __rhs.destip)
        {
            return false;
        }
        if(destport != __rhs.destport)
        {
            return false;
        }
        if(ssrc != __rhs.ssrc)
        {
            return false;
        }
        if(sdk != __rhs.sdk)
        {
            return false;
        }
        return true;
    }

    bool operator<(const RealStreamReqParam& __rhs) const
    {
        if(this == &__rhs)
        {
            return false;
        }
        if(id < __rhs.id)
        {
            return true;
        }
        else if(__rhs.id < id)
        {
            return false;
        }
        if(callid < __rhs.callid)
        {
            return true;
        }
        else if(__rhs.callid < callid)
        {
            return false;
        }
        if(ip < __rhs.ip)
        {
            return true;
        }
        else if(__rhs.ip < ip)
        {
            return false;
        }
        if(port < __rhs.port)
        {
            return true;
        }
        else if(__rhs.port < port)
        {
            return false;
        }
        if(name < __rhs.name)
        {
            return true;
        }
        else if(__rhs.name < name)
        {
            return false;
        }
        if(pwd < __rhs.pwd)
        {
            return true;
        }
        else if(__rhs.pwd < pwd)
        {
            return false;
        }
        if(destip < __rhs.destip)
        {
            return true;
        }
        else if(__rhs.destip < destip)
        {
            return false;
        }
        if(destport < __rhs.destport)
        {
            return true;
        }
        else if(__rhs.destport < destport)
        {
            return false;
        }
        if(ssrc < __rhs.ssrc)
        {
            return true;
        }
        else if(__rhs.ssrc < ssrc)
        {
            return false;
        }
        if(sdk < __rhs.sdk)
        {
            return true;
        }
        else if(__rhs.sdk < sdk)
        {
            return false;
        }
        return false;
    }

    bool operator!=(const RealStreamReqParam& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const RealStreamReqParam& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const RealStreamReqParam& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const RealStreamReqParam& __rhs) const
    {
        return !operator<(__rhs);
    }
};

}

namespace Ice
{
template<>
struct StreamableTraits< ::Media::RequestCanceledException>
{
    static const StreamHelperCategory helper = StreamHelperCategoryUserException;
};

template<>
struct StreamableTraits< ::Media::RealStreamRespParam>
{
    static const StreamHelperCategory helper = StreamHelperCategoryStruct;
    static const int minWireSize = 4;
    static const bool fixedLength = false;
};

template<class S>
struct StreamWriter< ::Media::RealStreamRespParam, S>
{
    static void write(S* __os, const ::Media::RealStreamRespParam& v)
    {
        __os->write(v.id);
        __os->write(v.callid);
        __os->write(v.sourceip);
        __os->write(v.sourceport);
    }
};

template<class S>
struct StreamReader< ::Media::RealStreamRespParam, S>
{
    static void read(S* __is, ::Media::RealStreamRespParam& v)
    {
        __is->read(v.id);
        __is->read(v.callid);
        __is->read(v.sourceip);
        __is->read(v.sourceport);
    }
};

template<>
struct StreamableTraits< ::Media::RealStreamReqParam>
{
    static const StreamHelperCategory helper = StreamHelperCategoryStruct;
    static const int minWireSize = 19;
    static const bool fixedLength = false;
};

template<class S>
struct StreamWriter< ::Media::RealStreamReqParam, S>
{
    static void write(S* __os, const ::Media::RealStreamReqParam& v)
    {
        __os->write(v.id);
        __os->write(v.callid);
        __os->write(v.ip);
        __os->write(v.port);
        __os->write(v.name);
        __os->write(v.pwd);
        __os->write(v.destip);
        __os->write(v.destport);
        __os->write(v.ssrc);
        __os->write(v.sdk);
    }
};

template<class S>
struct StreamReader< ::Media::RealStreamReqParam, S>
{
    static void read(S* __is, ::Media::RealStreamReqParam& v)
    {
        __is->read(v.id);
        __is->read(v.callid);
        __is->read(v.ip);
        __is->read(v.port);
        __is->read(v.name);
        __is->read(v.pwd);
        __is->read(v.destip);
        __is->read(v.destport);
        __is->read(v.ssrc);
        __is->read(v.sdk);
    }
};

}

namespace Media
{

class AMD_Stream_openRealStream : virtual public ::Ice::AMDCallback
{
public:

    virtual void ice_response(const ::Media::RealStreamRespParam&) = 0;
};

typedef ::IceUtil::Handle< ::Media::AMD_Stream_openRealStream> AMD_Stream_openRealStreamPtr;

}

namespace IceAsync
{

namespace Media
{

class AMD_Stream_openRealStream : public ::Media::AMD_Stream_openRealStream, public ::IceInternal::IncomingAsync
{
public:

    AMD_Stream_openRealStream(::IceInternal::Incoming&);

    virtual void ice_response(const ::Media::RealStreamRespParam&);
    // COMPILERFIX: The using directive avoid compiler warnings with -Woverloaded-virtual
    using ::IceInternal::IncomingAsync::ice_exception;
    virtual void ice_exception(const ::std::exception&);
};

}

}

namespace Media
{

class Callback_Stream_openRealStream_Base : virtual public ::IceInternal::CallbackBase { };
typedef ::IceUtil::Handle< Callback_Stream_openRealStream_Base> Callback_Stream_openRealStreamPtr;

}

namespace IceProxy
{

namespace Media
{

class Stream : virtual public ::IceProxy::Ice::Object
{
public:

    void openRealStream(const ::Media::RealStreamReqParam& __p_ctg, ::Media::RealStreamRespParam& __p_stm)
    {
        openRealStream(__p_ctg, __p_stm, 0);
    }
    void openRealStream(const ::Media::RealStreamReqParam& __p_ctg, ::Media::RealStreamRespParam& __p_stm, const ::Ice::Context& __ctx)
    {
        openRealStream(__p_ctg, __p_stm, &__ctx);
    }
#ifdef ICE_CPP11
    ::Ice::AsyncResultPtr
    begin_openRealStream(const ::Media::RealStreamReqParam& __p_ctg, const ::IceInternal::Function<void (const ::Media::RealStreamRespParam&)>& __response, const ::IceInternal::Function<void (const ::Ice::Exception&)>& __exception = ::IceInternal::Function<void (const ::Ice::Exception&)>(), const ::IceInternal::Function<void (bool)>& __sent = ::IceInternal::Function<void (bool)>())
    {
        return __begin_openRealStream(__p_ctg, 0, __response, __exception, __sent);
    }
    ::Ice::AsyncResultPtr
    begin_openRealStream(const ::Media::RealStreamReqParam& __p_ctg, const ::IceInternal::Function<void (const ::Ice::AsyncResultPtr&)>& __completed, const ::IceInternal::Function<void (const ::Ice::AsyncResultPtr&)>& __sent = ::IceInternal::Function<void (const ::Ice::AsyncResultPtr&)>())
    {
        return begin_openRealStream(__p_ctg, 0, ::Ice::newCallback(__completed, __sent), 0);
    }
    ::Ice::AsyncResultPtr
    begin_openRealStream(const ::Media::RealStreamReqParam& __p_ctg, const ::Ice::Context& __ctx, const ::IceInternal::Function<void (const ::Media::RealStreamRespParam&)>& __response, const ::IceInternal::Function<void (const ::Ice::Exception&)>& __exception = ::IceInternal::Function<void (const ::Ice::Exception&)>(), const ::IceInternal::Function<void (bool)>& __sent = ::IceInternal::Function<void (bool)>())
    {
        return __begin_openRealStream(__p_ctg, &__ctx, __response, __exception, __sent);
    }
    ::Ice::AsyncResultPtr
    begin_openRealStream(const ::Media::RealStreamReqParam& __p_ctg, const ::Ice::Context& __ctx, const ::IceInternal::Function<void (const ::Ice::AsyncResultPtr&)>& __completed, const ::IceInternal::Function<void (const ::Ice::AsyncResultPtr&)>& __sent = ::IceInternal::Function<void (const ::Ice::AsyncResultPtr&)>())
    {
        return begin_openRealStream(__p_ctg, &__ctx, ::Ice::newCallback(__completed, __sent));
    }
    
private:

    ::Ice::AsyncResultPtr __begin_openRealStream(const ::Media::RealStreamReqParam& __p_ctg, const ::Ice::Context* __ctx, const ::IceInternal::Function<void (const ::Media::RealStreamRespParam&)>& __response, const ::IceInternal::Function<void (const ::Ice::Exception&)>& __exception, const ::IceInternal::Function<void (bool)>& __sent);
    
public:
#endif

    ::Ice::AsyncResultPtr begin_openRealStream(const ::Media::RealStreamReqParam& __p_ctg)
    {
        return begin_openRealStream(__p_ctg, 0, ::IceInternal::__dummyCallback, 0);
    }

    ::Ice::AsyncResultPtr begin_openRealStream(const ::Media::RealStreamReqParam& __p_ctg, const ::Ice::Context& __ctx)
    {
        return begin_openRealStream(__p_ctg, &__ctx, ::IceInternal::__dummyCallback, 0);
    }

    ::Ice::AsyncResultPtr begin_openRealStream(const ::Media::RealStreamReqParam& __p_ctg, const ::Ice::CallbackPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return begin_openRealStream(__p_ctg, 0, __del, __cookie);
    }

    ::Ice::AsyncResultPtr begin_openRealStream(const ::Media::RealStreamReqParam& __p_ctg, const ::Ice::Context& __ctx, const ::Ice::CallbackPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return begin_openRealStream(__p_ctg, &__ctx, __del, __cookie);
    }

    ::Ice::AsyncResultPtr begin_openRealStream(const ::Media::RealStreamReqParam& __p_ctg, const ::Media::Callback_Stream_openRealStreamPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return begin_openRealStream(__p_ctg, 0, __del, __cookie);
    }

    ::Ice::AsyncResultPtr begin_openRealStream(const ::Media::RealStreamReqParam& __p_ctg, const ::Ice::Context& __ctx, const ::Media::Callback_Stream_openRealStreamPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return begin_openRealStream(__p_ctg, &__ctx, __del, __cookie);
    }

    void end_openRealStream(::Media::RealStreamRespParam& __p_stm, const ::Ice::AsyncResultPtr&);
    
private:

    void openRealStream(const ::Media::RealStreamReqParam&, ::Media::RealStreamRespParam&, const ::Ice::Context*);
    ::Ice::AsyncResultPtr begin_openRealStream(const ::Media::RealStreamReqParam&, const ::Ice::Context*, const ::IceInternal::CallbackBasePtr&, const ::Ice::LocalObjectPtr& __cookie = 0);
    
public:
    
    ::IceInternal::ProxyHandle<Stream> ice_context(const ::Ice::Context& __context) const
    {
        return dynamic_cast<Stream*>(::IceProxy::Ice::Object::ice_context(__context).get());
    }
    
    ::IceInternal::ProxyHandle<Stream> ice_adapterId(const ::std::string& __id) const
    {
        return dynamic_cast<Stream*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    }
    
    ::IceInternal::ProxyHandle<Stream> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
        return dynamic_cast<Stream*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    }
    
    ::IceInternal::ProxyHandle<Stream> ice_locatorCacheTimeout(int __timeout) const
    {
        return dynamic_cast<Stream*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    }
    
    ::IceInternal::ProxyHandle<Stream> ice_connectionCached(bool __cached) const
    {
        return dynamic_cast<Stream*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    }
    
    ::IceInternal::ProxyHandle<Stream> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
        return dynamic_cast<Stream*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    }
    
    ::IceInternal::ProxyHandle<Stream> ice_secure(bool __secure) const
    {
        return dynamic_cast<Stream*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    }
    
    ::IceInternal::ProxyHandle<Stream> ice_preferSecure(bool __preferSecure) const
    {
        return dynamic_cast<Stream*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    }
    
    ::IceInternal::ProxyHandle<Stream> ice_router(const ::Ice::RouterPrx& __router) const
    {
        return dynamic_cast<Stream*>(::IceProxy::Ice::Object::ice_router(__router).get());
    }
    
    ::IceInternal::ProxyHandle<Stream> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
        return dynamic_cast<Stream*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    }
    
    ::IceInternal::ProxyHandle<Stream> ice_collocationOptimized(bool __co) const
    {
        return dynamic_cast<Stream*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    }
    
    ::IceInternal::ProxyHandle<Stream> ice_invocationTimeout(int __timeout) const
    {
        return dynamic_cast<Stream*>(::IceProxy::Ice::Object::ice_invocationTimeout(__timeout).get());
    }
    
    ::IceInternal::ProxyHandle<Stream> ice_twoway() const
    {
        return dynamic_cast<Stream*>(::IceProxy::Ice::Object::ice_twoway().get());
    }
    
    ::IceInternal::ProxyHandle<Stream> ice_oneway() const
    {
        return dynamic_cast<Stream*>(::IceProxy::Ice::Object::ice_oneway().get());
    }
    
    ::IceInternal::ProxyHandle<Stream> ice_batchOneway() const
    {
        return dynamic_cast<Stream*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    }
    
    ::IceInternal::ProxyHandle<Stream> ice_datagram() const
    {
        return dynamic_cast<Stream*>(::IceProxy::Ice::Object::ice_datagram().get());
    }
    
    ::IceInternal::ProxyHandle<Stream> ice_batchDatagram() const
    {
        return dynamic_cast<Stream*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    }
    
    ::IceInternal::ProxyHandle<Stream> ice_compress(bool __compress) const
    {
        return dynamic_cast<Stream*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    }
    
    ::IceInternal::ProxyHandle<Stream> ice_timeout(int __timeout) const
    {
        return dynamic_cast<Stream*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    }
    
    ::IceInternal::ProxyHandle<Stream> ice_connectionId(const ::std::string& __id) const
    {
        return dynamic_cast<Stream*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    }
    
    ::IceInternal::ProxyHandle<Stream> ice_encodingVersion(const ::Ice::EncodingVersion& __v) const
    {
        return dynamic_cast<Stream*>(::IceProxy::Ice::Object::ice_encodingVersion(__v).get());
    }
    
    static const ::std::string& ice_staticId();

private: 
    virtual ::IceProxy::Ice::Object* __newInstance() const;
};

}

}

namespace Media
{

class Stream : virtual public ::Ice::Object
{
public:

    typedef StreamPrx ProxyType;
    typedef StreamPtr PointerType;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void openRealStream_async(const ::Media::AMD_Stream_openRealStreamPtr&, const ::Media::RealStreamReqParam&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___openRealStream(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

protected:
    virtual void __writeImpl(::IceInternal::BasicStream*) const;
    virtual void __readImpl(::IceInternal::BasicStream*);
    using ::Ice::Object::__writeImpl;
    using ::Ice::Object::__readImpl;
};

inline bool operator==(const Stream& l, const Stream& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

inline bool operator<(const Stream& l, const Stream& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

}

namespace Media
{

template<class T>
class CallbackNC_Stream_openRealStream : public Callback_Stream_openRealStream_Base, public ::IceInternal::TwowayCallbackNC<T>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception&);
    typedef void (T::*Sent)(bool);
    typedef void (T::*Response)(const ::Media::RealStreamRespParam&);

    CallbackNC_Stream_openRealStream(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::TwowayCallbackNC<T>(obj, cb != 0, excb, sentcb), _response(cb)
    {
    }

    virtual void completed(const ::Ice::AsyncResultPtr& __result) const
    {
        ::Media::StreamPrx __proxy = ::Media::StreamPrx::uncheckedCast(__result->getProxy());
        ::Media::RealStreamRespParam stm;
        try
        {
            __proxy->end_openRealStream(stm, __result);
        }
        catch(const ::Ice::Exception& ex)
        {
            ::IceInternal::CallbackNC<T>::exception(__result, ex);
            return;
        }
        if(_response)
        {
            (::IceInternal::CallbackNC<T>::_callback.get()->*_response)(stm);
        }
    }

    private:

    Response _response;
};

template<class T> Callback_Stream_openRealStreamPtr
newCallback_Stream_openRealStream(const IceUtil::Handle<T>& instance, void (T::*cb)(const ::Media::RealStreamRespParam&), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_Stream_openRealStream<T>(instance, cb, excb, sentcb);
}

template<class T> Callback_Stream_openRealStreamPtr
newCallback_Stream_openRealStream(T* instance, void (T::*cb)(const ::Media::RealStreamRespParam&), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_Stream_openRealStream<T>(instance, cb, excb, sentcb);
}

template<class T, typename CT>
class Callback_Stream_openRealStream : public Callback_Stream_openRealStream_Base, public ::IceInternal::TwowayCallback<T, CT>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception& , const CT&);
    typedef void (T::*Sent)(bool , const CT&);
    typedef void (T::*Response)(const ::Media::RealStreamRespParam&, const CT&);

    Callback_Stream_openRealStream(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::TwowayCallback<T, CT>(obj, cb != 0, excb, sentcb), _response(cb)
    {
    }

    virtual void completed(const ::Ice::AsyncResultPtr& __result) const
    {
        ::Media::StreamPrx __proxy = ::Media::StreamPrx::uncheckedCast(__result->getProxy());
        ::Media::RealStreamRespParam stm;
        try
        {
            __proxy->end_openRealStream(stm, __result);
        }
        catch(const ::Ice::Exception& ex)
        {
            ::IceInternal::Callback<T, CT>::exception(__result, ex);
            return;
        }
        if(_response)
        {
            (::IceInternal::Callback<T, CT>::_callback.get()->*_response)(stm, CT::dynamicCast(__result->getCookie()));
        }
    }

    private:

    Response _response;
};

template<class T, typename CT> Callback_Stream_openRealStreamPtr
newCallback_Stream_openRealStream(const IceUtil::Handle<T>& instance, void (T::*cb)(const ::Media::RealStreamRespParam&, const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_Stream_openRealStream<T, CT>(instance, cb, excb, sentcb);
}

template<class T, typename CT> Callback_Stream_openRealStreamPtr
newCallback_Stream_openRealStream(T* instance, void (T::*cb)(const ::Media::RealStreamRespParam&, const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_Stream_openRealStream<T, CT>(instance, cb, excb, sentcb);
}

}

#include <IceUtil/PopDisableWarnings.h>
#endif
