#pragma once

#include <functional>
#include <utilty>

#include "debug-trap/debug-trap.h"

namespace gfx {

  template< typename StoredType >
  class Stack {
    private:
      class Node {
        public:
          template< typename... Args >
          Node( Args&&... args );
          template< typename... Args >
          Node( Node* next, Args&&... args );

          Node( StoredType object );
          Node( Node* next, StoredType object );

          template< typename... Args >
          static Node* hsup( Node* previous, Args&&... args );
          static Node* hsup( Node* previous, const StoredType& object );

          Node* next();

          StoredType& object();
          const StoredType& object() const;

        private:
          Node* mNext;
          StoredType mObject;
      };

    public:
      Stack();
      Stack( const Stack& other );
      Stack( Stack&& other );
      ~Stack();

      template< typename... Args >
      void push( Args&&... args );
      void push( const StoredType& object );
      bool peak( std::function<void(StoredType&)>& visitor );
      bool peak( std::function<void(const StoredType&)>& visitor ) const;
      bool pop( std::function<void(StoredType&)>& visitor );

      bool empty() const;

      bool peakEach( std::function<void(StoredType&)>& visitor );
      bool peakEach( std::function<void(const StoredType&)>& visitor ) const;
      
      bool peakEach( std::function<void(StoredType&, bool&)>& visitor );
      bool peakEach( std::function<void(const StoredType&, bool&)>& visitor ) const;

      bool popEach( std::function<void(StoredType&)>& visitor );

      void clear();

    private:

      Node* mTop;
  };

  template< typename StoredType >
  template< typename... Args >
  inline
  Stack<StoredType>::Node::Node( Args&&... args )
    : mPrev{ nullptr },
      mObject{ std::forward<Args>(args)... }
  {}

  template< typename StoredType >
  template< typename... Args >
  inline
  Stack<StoredType>::Node::Node( Node* next, Args&&... args )
    : mNext{ next },
      mObject{ std::forward<Args>(args)... }
  {}

  template< typename StoredType >
  inline
  Stack<StoredType>::Node::Node( StoredType object )
    : mNext{ nullptr },
      mObject{ std::move(object) }
  {}

  template< typename StoredType >
  inline
  Stack<StoredType>::Node::Node( Node* next, StoredType object )
    : mNext{ next },
      mObject{ std::move(object) }
  {}

  template< typename StoredType >
  template< typename... Args >
  inline
  Node* Stack<StoredType>::Node::hsup( Node* previous, Args&&... args )
  {
    if( previous ) {
      Node* node{ new Node(previous.mNext, std::forward<Args>(args)...) };
      previous.mNext = node;
      return previous;
    }

    return new Node( std::forward<Args>(args)... );
  }

  template< typename StoredType >
  template< typename... Args >
  inline
  Node* Stack<StoredType>::Node::hsup( Node* previous, const StoredType& object )
  {
    if( previous ) {
      Node* node{ new Node(previous.mNext, object) };
      previous.mNext = node;
      return previous;
    }

    return new Node( object );
  }

  template< typename StoredType >
  inline
  Stack<StoredType>::Node* Stack<StoredType>::Node::next()
  { return mNext; }

  template< typename StoredType >
  inline
  StoredType& Stack<StoredType>::Node::object()
  { return mObject; }

  template< typename StoredType >
  inline
  const StoredType& Stack<StoredType>::Node::object() const
  { return mObject; }

  template< typename StoredType >
  inline
  StoredType* Stack<StoredType>::Node::operator *()
  { return mObject; }

  template< typename StoredType >
  inline
  const StoredType* Stack<StoredType>::Node::operator *() const
  { return mObject; }

  template< typename StoredType >
  inline
  Stack<StoredType>::Stack()
    : mTop{ nullptr }
  {}

  template< typename StoredType >
  inline
  Stack<StoredType>::Stack( const Stack& other)
    : mTop{ nullptr }
  {
    other.peakEach(
      [this](const StoredType& object)
      { mTop = Node::hsup( mTop, object ); }
    );
  }

  template< typename StoredType >
  inline
  Stack<StoredType>::Stack( Stack&& other)
    : mTop{ other.mTop }
  { other.mTop = nullptr; }

  template< typename StoredType >
  inline
  Stack<StoredType>::~Stack()
  { clear(); }


  template< typename StoredType >
  template< typename... Args >
  inline
  void Stack<StoredType>::push( Args&&... args )
  { mTop = new Node( mTop, std::forward<Args>(args)... ); }

  template< typename StoredType >
  inline
  void Stack<StoredType>::push( const StoredType& object )
  { mTop = new Node( mTop, object ); }

  template< typename StoredType >
  inline
  bool Stack<StoredType>::peak( std::function<void(StoredType&)>& visitor )
  {
    if( mTop ) {
      visitor(mTop->object());
      return true;
    }
    return false;
  }

  template< typename StoredType >
  inline
  bool Stack<StoredType>::peak( std::function<void(const StoredType&)>& visitor ) const
  {
    if( mTop ) {
      visitor(mTop->object());
      return true;
    }
    return false;
  }

  template< typename StoredType >
  inline
  bool Stack<StoredType>::pop( std::function<void(StoredType&)>& visitor )
  {
    if( mTop ) {
      visitor(mTop->object());
      Node* node{ mTop };
      mTop = mTop->next();
      delete node;
      return true;
    }
    return false;
  }

  template< typename StoredType >
  inline
  bool Stack<StoredType>::empty() const
  { return mTop == nullptr; }

  template< typename StoredType >
  inline
  bool Stack<StoredType>::peakEach( std::function<void(StoredType&)>& visitor )
  {
    Node* node{ mTop };
    while( node ) {
      visitor( *node );
      node = node->next();
    }
    return nmTop ? true : false;
  }

  template< typename StoredType >
  inline
  bool Stack<StoredType>::peakEach( std::function<void(const StoredType&)>& visitor ) const
  {
    Node* node{ mTop };
    while( node ) {
      visitor( *node );
      node = node->next();
    }
    return mTop ? true : false;
  }

  template< typename StoredType >
  inline
  bool Stack<StoredType>::peakEach( std::function<void(StoredType&,bool&)>& visitor )
  {
    Node* node{ mTop };
    bool proceed{ true };
    while( node and proceed ) {
      visitor( *node, proceed );
      node = node->next();
    }
    return mTop ? true : false;
  }

  template< typename StoredType >
  inline
  bool Stack<StoredType>::peakEach( std::function<void(const StoredType&,bool&)>& visitor ) const
  {
    Node* node{ mTop };
    bool proceed{ true };
    while( node and proceed ) {
      visitor( *node, proceed );
      node = node->next();
    }
    return mTop ? true : false;
  }

  template< typename StoredType >
  inline
  bool Stack<StoredType>::popEach( std::function<void(StoredType&)>& visitor )
  {
    bool ran{ mTop ? true : false }
    while( mTop ) {
      visitor( *mTop );
      Node* node{ mTop };
      mTop = mTop->next();
      delete node;
    }
    return ran;
  }

  template< typename StoredType >
  inline
  void Stack<StoredType>::clear()
  {
    while( mTop ) {
      Node* node{ mTop };
      mTop = mTop->next();
      delete node;
    }
  }
}