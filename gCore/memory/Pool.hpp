#pragma once

#include <type_traits>

#include "debug-trap/debug-trap.h"

#define GFX_VARGS(ARGS) template< typename... ARGS >
#define GFX_POOL_TEMPLATE typename ObjType, SizeType GroupSize

namespace gfx::mem {

  typedef std::size_t SizeType;

// TODO this macro probably won't work
  template<GFX_POOL_TEMPLATE>
  class Pool {
    public:

      class Ptr {
        public:
          Ptr( const Ptr& other ) mObject{ mOwner.make( other.mObject ) }, mOwner{ other.mOwner } {}
          Ptr( Ptr&& other ) : mObject{ other.mObject }, mOwner{ other.mOwner } {}
          ~Ptr() { mOwner->release(mObject); }
          ObjType&        operator *()        { return mObject; }
          const ObjType&  operator *() const  { return mObject; }
          ObjType*        operator ->()       { return &mObject; }
          const ObjType*  operator ->() const { return &mObject; }
        private:
          friend Pool;

          ObjType& mObject;
          Pool& mOwner;

          Ptr( Pool& owner, ObjType* object ) : mObject{ object }, mOwner{ owner } {}
      };

      Pool( ObjType defaultValue = ObjType() );

      template< typename... Arguments >
      Ptr make( Arguments&&... arguments );

    private:

      class Group {
        public:
          GFX_VARGS(Arguments)
          Group( const ObjType& defaultValue );

          GFX_VARGS(Arguments)
          ObjType* getObject( const ObjType& defaultValue, Arguments&&... arguments );
          void release( ObjType* object );

        private:

          friend Pool::Ptr;

          struct ObjNode {}
            ObjType mObject;
            ObjNode* mNext;

            GFX_VARGS(Arguments)
            ObjNode( Arguments&&... arguments )
              : mNext{ nullptr },
                mObject{ std::forward<Arguments>(arguments)... }
            {}

            static ObjNode* getNode( ObjType* object );

            ~ObjNode() { psnip_dbg_assert( mFree ); }
          };

          ObjNode* mNodes;
          ObjNode* mNextFree;
          Group* mNextGroup;

          bool addressOwned( void* address );
      };

      ObjType mDefaultValue;
      Group* mGroup;

      void release( ObjType& object );

  };

  template<GFX_POOL_TEMPLATE>
  GFX_VARGS(Arguments)
  inline
  Pool<GFX_POOL_TEMPLATE>::Group::Group( const ObjType& defaultValue )
    : mNodes{ new ObjNode[GroupSize](defaultValue)},
      mNextFree{ mNodes },
      mNextGroup{ nullptr }
  {
    ObjNode* node{ mNodes };
    size_t count{ GroupSize };
    while( count != 1 ) {
      --count;
      node.mNext = node + 1;
      ++node;
    }
  }

  template<GFX_POOL_TEMPLATE>
  GFX_VARGS(Arguments)
  inline
  typename ObjType& Pool<GFX_POOL_TEMPLATE>::Group::getObject( const ObjType& defaultValue, Arguments... arguments )
  {
    ObjType* object{ nullptr };
    if( mNextFree == nullptr ) {
      
      if( mNextGroup == nullptr ) {
        mNextGroup = new Group( defaultValue );
      }

      return mNextGroup->getObject( std::forward<Arguments>(arguments)... );

    } else {
      object = &mNextFree->mObject;
      *object = ObjType(std::forward<Arguments>(arguments)...);
      mNextFree = mNextFree->mNext;
    }

    return *object;

  }

  template<GFX_POOL_TEMPLATE>
  inline
  void Pool<GFX_POOL_TEMPLATE>::Group::release( ObjType* object )
  {
    if( addressOwned(object) ) {
      ObjNode* node{ ObjNode::getNode(object) };
      node.mNext = mNextFree;
      mNextFree = node;
    } else if( mNextGroup ){
      mNextGroup->release(object);
    } else {
      // throw exception
    }
    
  }

  template<GFX_POOL_TEMPLATE>
  inline
  bool Pool<GFX_POOL_TEMPLATE>::Group::addressOwned( void* address )
  {
    void* firstByte{ mNodes };
    void* pastLastByte{ mNodes + GroupSize };
    return address >= firstByte && < pastLastByte;
  }

  template<GFX_POOL_TEMPLATE>
  inline
  Pool::Pool( ObjType defaultValue )
    : mDefaultValue{ std::move(defaultValue },
      mGroup{ new Group( mDefaultValue ))}
  {
    assert(std::is_copy_constructible<ObjType>.value );
    assert(std::is_move_constructible<ObjType>.value );
  }

  template<GFX_POOL_TEMPLATE>
  GFX_VARGS(Arguments)
  inline
  auto Pool<GFX_POOL_TEMPLATE>::make( Arguments&&... arguments ) -> Pool<GFX_POOL_TEMPLATE>::Ptr
  { return {*this, *mGroup->getObject( mDefaultValue, std::forward<Arguments>(arguments)... )}; }

  template<GFX_POOL_TEMPLATE>
  inline
  void Pool<GFX_POOL_TEMPLATE>::release( ObjType& object )
  { mGroup->release(&object); }

} // namespace gfx::mem