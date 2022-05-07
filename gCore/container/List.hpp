#pragma once

#include <functional>
#include <utilty>

#include "debug-trap/debug-trap.h"

namespace gfx {

  template< typename StoredType >
  class List {
    private:
      class Node {
        public:
          template< typename... Args >
          Node( Args&&... args );
          template< typename... Args >
          Node( Node* previous, Args&&... args );
          template< typename... Args >
          Node( Node* previous, Node* next, Args&&... args );

          Node( StoredType object );
          Node( Node* previous, StoredType object );
          Node( Node* previous, Node* next, StoredType object );

          Node* previous();
          Node* next();

          StoredType& object();
          const StoredType& object() const;

        private:
          Node* mPrev;
          Node* mNext;
          StoredType mObject;
      };

    public:
      List();
      List( const List& other );
      List( List&& other );
      ~List();

      template< typename... Args >
      void append( Args&&... args );
      void append( const StoredType& object );

      template< typename... Args >
      void prepend( Args&&... args );
      void prepend( const StoredType& object );

      bool empty() const;

      bool forEach( std::function<void(StoredType&)>& visitor );
      bool forEach( std::function<void(const StoredType&)>& visitor ) const;
      bool forEachReversed( std::function<void(StoredType&)>& visitor );
      bool forEachReversed( std::function<void(const StoredType&)>& visitor ) const;
      
      bool forEach( std::function<void(StoredType&, bool&)>& visitor );
      bool forEach( std::function<void(const StoredType&, bool&)>& visitor ) const;
      bool forEachReversed( std::function<void(StoredType&, bool&)>& visitor );
      bool forEachReversed( std::function<void(const StoredType&, bool&)>& visitor ) const;

      void clear();

    private:

      Node* mFront;
      Node* mBack;
  };

  template< typename StoredType >
  template< typename... Args >
  inline
  List<StoredType>::Node::Node( Args&&... args )
    : mPrev{ nullptr },
      mNext{ nullptr },
      mObject{ std::forward<Args>(args)... }
  {}

  template< typename StoredType >
  template< typename... Args >
  inline
  List<StoredType>::Node::Node( Node* previous, Args&&... args )
    : mPrev{ previous },
      mNext{ nullptr },
      mObject{ std::forward<Args>(args)... }
  {}

  template< typename StoredType >
  template< typename... Args >
  inline
  List<StoredType>::Node::Node( Node* previous, Node* next, Args&&... args )
    : mPrev{ previous },
      mNext{ next },
      mObject{ std::forward<Args>(args)... }
  {}

  template< typename StoredType >
  inline
  List<StoredType>::Node::Node( StoredType object )
    : mPrev{ nullptr },
      mNext{ nullptr },
      mObject{ std::move(object) }
  {}

  template< typename StoredType >
  inline
  List<StoredType>::Node::Node( Node* previous, StoredType object )
    : mPrev{ previous },
      mNext{ nullptr },
      mObject{ std::move(object) }
  {}

  template< typename StoredType >
  inline
  List<StoredType>::Node::Node( Node* previous, Node* next, StoredType object )
    : mPrev{ previous },
      mNext{ next },
      mObject{ std::move(object) }
  {}

  template< typename StoredType >
  inline
  List<StoredType>::Node* List<StoredType>::Node::next()
  { return mNext; }

  template< typename StoredType >
  inline
  StoredType& List<StoredType>::Node::object()
  { return mObject; }

  template< typename StoredType >
  inline
  const StoredType& List<StoredType>::Node::object() const
  { return mObject; }

  template< typename StoredType >
  inline
  List<StoredType>::List()
    : mFront{ nullptr },
      mBack{ nullptr }
  {}

  template< typename StoredType >
  inline
  List<StoredType>::List( const List& other )
    : mFront{ nullptr },
      mBack{ nullptr }
  { other.forEach( [this]( const StoredType& object ){ append(object); } ); }

  template< typename StoredType >
  inline
  List<StoredType>::List( List&& other )
    : mFront{ other.mFront },
      mBack{ other.mBack }
  {
    other.mFront = nullptr;
    other.mBack = nullptr;
  }

  template< typename StoredType >
  inline
  List<StoredType>::~List()
  { clear(); }

  template< typename StoredType >
  template< typename... Args >
  inline
  void append( Args&&... args )
  {
    if( mFront ) {
      psnip_dbg_assert( mBack );
      mBack = new Node( mBack, std::forward<Args>(args)...);
    } else {
      psnip_dbg_assert( not mBack );
      mFront = new Node( std::forward<Args>(args)...);
      mBack = mFront;
    }
  }

  template< typename StoredType >
  inline
  void append( const StoredType& object )
  {
    if( mFront ) {
      psnip_dbg_assert( mBack );
      mBack = new Node( mBack, std::forward<Args>(args)...);
    } else {
      psnip_dbg_assert( not mBack );
      mFront = new Node( std::forward<Args>(args)...);
      mBack = mFront;
    }
  }

  template< typename StoredType >
  template< typename... Args >
  inline
  void prepend( Args&&... args )
  {
    if( mFront ) {
      psnip_dbg_assert( mBack );
      mFront = new Node( nullptr, mFront, std::forward<Args>(args)...);
    } else {
      psnip_dbg_assert( not mBack );
      mFront = new Node( std::forward<Args>(args)...);
      mBack = mFront;
    }
  }

  template< typename StoredType >
  inline
  bool empty() const
  {
    psnip_dbg_assert( (mFront and mBack) or not (mFront or mBack) );
    return mFront == nullptr;
  }

  template< typename StoredType >
  inline
  bool List<StoredType>::forEach( std::function<void(StoredType&)>& visitor )
  {
    Node* node{ mFront };
    while(node) {
      visitor( *node );
      node = node->next();
    }
  }

  template< typename StoredType >
  inline
  bool List<StoredType>::forEach( std::function<void(const StoredType&)>& visitor ) const
  {
    const Node* node{ mFront };
    while(node) {
      visitor( *node );
      node = node->next();
    }
  }

  template< typename StoredType >
  inline
  bool List<StoredType>::forEachReversed( std::function<void(StoredType&)>& visitor )
  {
    Node* node{ mBack };
    while(node) {
      visitor( *node );
      node = node->previous();
    }
  }

  template< typename StoredType >
  inline
  bool List<StoredType>::forEachReversed( std::function<void(const StoredType&)>& visitor ) const
  {
    const Node* node{ mBack };
    while(node) {
      visitor( *node );
      node = node->previous();
    }
  }

  template< typename StoredType >
  inline
  bool List<StoredType>::forEach( std::function<void(StoredType&,bool&)>& visitor )
  {
    Node* node{ mFront };
    bool proceed{ true };
    while(node and proceed) {
      visitor( *node, proceed );
      node = node->next();
    }
  }

  template< typename StoredType >
  inline
  bool List<StoredType>::forEach( std::function<void(const StoredType&, bool&)>& visitor ) const
  {
    const Node* node{ mFront };
    bool proceed{ true };
    while(node and proceed) {
      visitor( *node, proceed );
      node = node->next();
    }
  }

  template< typename StoredType >
  inline
  bool List<StoredType>::forEachReversed( std::function<void(StoredType&, bool&)>& visitor )
  {
    Node* node{ mBack };
    bool proceed{ true };
    while(node and proceed) {
      visitor( *node, proceed );
      node = node->previous();
    }
  }

  template< typename StoredType >
  inline
  bool List<StoredType>::forEachReversed( std::function<void(const StoredType&, bool&)>& visitor ) const
  {
    const Node* node{ mBack };
    bool proceed{ true };
    while(node and proceed) {
      visitor( *node );
      node = node->previous();
    }
  }

  template< typename StoredType >
  inline
  void List<StoredType>::clear()
  {
    Node* node{ mFront };
    while(node) {
      Node* next{ node->next() };
      delete node;
      node = next;
    }
  }
}