// list standard header
#pragma once
#ifndef _LIST_
#define _LIST_
#ifndef RC_INVOKED
#include <xmemory>
#include <stdexcept>

 #pragma pack(push,_CRT_PACKING)
 #pragma warning(push,_STL_WARNING_LEVEL)
 #pragma warning(disable: _STL_DISABLED_WARNINGS)
 #pragma push_macro("new")
 #undef new

_STD_BEGIN
		// CLASS TEMPLATE _List_unchecked_const_iterator
template<class _Mylist,
	class _Base = _Iterator_base0>
	class _List_unchecked_const_iterator
		: public _Base
	{	// unchecked iterator for nonmutable list
public:
	using iterator_category = bidirectional_iterator_tag;

	using _Nodeptr = typename _Mylist::_Nodeptr;
	using value_type = typename _Mylist::value_type;
	using difference_type = typename _Mylist::difference_type;
	using pointer = typename _Mylist::const_pointer;
	using reference = const value_type&;

	_List_unchecked_const_iterator()
		: _Ptr()
		{	// construct with null node pointer
		}

	_List_unchecked_const_iterator(_Nodeptr _Pnode, const _Mylist *_Plist)
		: _Ptr(_Pnode)
		{	// construct with node pointer _Pnode
		this->_Adopt(_Plist);
		}

	reference operator*() const
		{	// return designated value
		return (_Ptr->_Myval);
		}

	pointer operator->() const
		{	// return pointer to class object
		return (pointer_traits<pointer>::pointer_to(**this));
		}

	_List_unchecked_const_iterator& operator++()
		{	// preincrement
		_Ptr = _Ptr->_Next;
		return (*this);
		}

	_List_unchecked_const_iterator operator++(int)
		{	// postincrement
		_List_unchecked_const_iterator _Tmp = *this;
		++*this;
		return (_Tmp);
		}

	_List_unchecked_const_iterator& operator--()
		{	// predecrement
		_Ptr = _Ptr->_Prev;
		return (*this);
		}

	_List_unchecked_const_iterator operator--(int)
		{	// postdecrement
		_List_unchecked_const_iterator _Tmp = *this;
		--*this;
		return (_Tmp);
		}

	bool operator==(const _List_unchecked_const_iterator& _Right) const
		{	// test for iterator equality
		return (_Ptr == _Right._Ptr);
		}

	bool operator!=(const _List_unchecked_const_iterator& _Right) const
		{	// test for iterator inequality
		return (!(*this == _Right));
		}

	_Nodeptr _Ptr;	// pointer to node
	};

	// CLASS TEMPLATE _List_unchecked_iterator
template<class _Mylist>
	class _List_unchecked_iterator
		: public _List_unchecked_const_iterator<_Mylist>
	{	// unchecked iterator for mutable list
public:
	using _Mybase = _List_unchecked_const_iterator<_Mylist>;
	using iterator_category = bidirectional_iterator_tag;

	using _Nodeptr = typename _Mylist::_Nodeptr;
	using value_type = typename _Mylist::value_type;
	using difference_type = typename _Mylist::difference_type;
	using pointer = typename _Mylist::pointer;
	using reference = value_type&;

	_List_unchecked_iterator()
		{	// construct with null node
		}

	_List_unchecked_iterator(_Nodeptr _Pnode, const _Mylist *_Plist)
		: _Mybase(_Pnode, _Plist)
		{	// construct with node pointer _Pnode
		}

	reference operator*() const
		{	// return designated value
		return ((reference)**(_Mybase *)this);
		}

	pointer operator->() const
		{	// return pointer to class object
		return (pointer_traits<pointer>::pointer_to(**this));
		}

	_List_unchecked_iterator& operator++()
		{	// preincrement
		++(*(_Mybase *)this);
		return (*this);
		}

	_List_unchecked_iterator operator++(int)
		{	// postincrement
		_List_unchecked_iterator _Tmp = *this;
		++*this;
		return (_Tmp);
		}

	_List_unchecked_iterator& operator--()
		{	// predecrement
		--(*(_Mybase *)this);
		return (*this);
		}

	_List_unchecked_iterator operator--(int)
		{	// postdecrement
		_List_unchecked_iterator _Tmp = *this;
		--*this;
		return (_Tmp);
		}
	};

	// CLASS TEMPLATE _List_const_iterator
template<class _Mylist>
	class _List_const_iterator
		: public _List_unchecked_const_iterator<_Mylist, _Iterator_base>
	{	// iterator for nonmutable list
public:
	using _Mybase = _List_unchecked_const_iterator<_Mylist, _Iterator_base>;
	using iterator_category = bidirectional_iterator_tag;

	using _Nodeptr = typename _Mylist::_Nodeptr;
	using value_type = typename _Mylist::value_type;
	using difference_type = typename _Mylist::difference_type;
	using pointer = typename _Mylist::const_pointer;
	using reference = const value_type&;

	_List_const_iterator()
		: _Mybase()
		{	// construct with null node pointer
		}

	_List_const_iterator(_Nodeptr _Pnode, const _Mylist *_Plist)
		: _Mybase(_Pnode, _Plist)
		{	// construct with node pointer _Pnode
		}

	using _Unchecked_type = _List_unchecked_const_iterator<_Mylist>;

	reference operator*() const
		{	// return designated value
 #if _ITERATOR_DEBUG_LEVEL == 2
		const auto _Mycont = static_cast<const _Mylist *>(this->_Getcont());
		if (_Mycont == 0
			|| this->_Ptr == nullptr
			|| this->_Ptr == _Mycont->_Myhead)
			{	// report error
			_DEBUG_ERROR("list iterator not dereferencable");
			}

 #elif _ITERATOR_DEBUG_LEVEL == 1
		_SCL_SECURE_VALIDATE(this->_Ptr != nullptr);
		const auto _Mycont = static_cast<const _Mylist *>(this->_Getcont());
		_SCL_SECURE_VALIDATE(_Mycont != 0);
		_SCL_SECURE_VALIDATE_RANGE(this->_Ptr != _Mycont->_Myhead);
 #endif /* _ITERATOR_DEBUG_LEVEL */

		return (this->_Ptr->_Myval);
		}

	pointer operator->() const
		{	// return pointer to class object
		return (pointer_traits<pointer>::pointer_to(**this));
		}

	_List_const_iterator& operator++()
		{	// preincrement
 #if _ITERATOR_DEBUG_LEVEL == 2
		const auto _Mycont = static_cast<const _Mylist *>(this->_Getcont());
		if (_Mycont == 0
			|| this->_Ptr == nullptr
			|| this->_Ptr == _Mycont->_Myhead)
			{	// report error
			_DEBUG_ERROR("list iterator not incrementable");
			}

 #elif _ITERATOR_DEBUG_LEVEL == 1
		_SCL_SECURE_VALIDATE(this->_Ptr != nullptr);
		const auto _Mycont = static_cast<const _Mylist *>(this->_Getcont());
		_SCL_SECURE_VALIDATE(_Mycont != 0);
		_SCL_SECURE_VALIDATE_RANGE(this->_Ptr != _Mycont->_Myhead);
 #endif /* _ITERATOR_DEBUG_LEVEL */

		this->_Ptr = this->_Ptr->_Next;
		return (*this);
		}

	_List_const_iterator operator++(int)
		{	// postincrement
		_List_const_iterator _Tmp = *this;
		++*this;
		return (_Tmp);
		}

	_List_const_iterator& operator--()
		{	// predecrement
 #if _ITERATOR_DEBUG_LEVEL == 2
		const auto _Mycont = static_cast<const _Mylist *>(this->_Getcont());
		if (_Mycont == 0
			|| this->_Ptr == nullptr
			|| (this->_Ptr = this->_Ptr->_Prev) == _Mycont->_Myhead)
			{	// report error
			_DEBUG_ERROR("list iterator not decrementable");
			}

 #elif _ITERATOR_DEBUG_LEVEL == 1
		_SCL_SECURE_VALIDATE(this->_Ptr != nullptr);
		const auto _Mycont = static_cast<const _Mylist *>(this->_Getcont());
		_SCL_SECURE_VALIDATE(_Mycont != 0);
		this->_Ptr = this->_Ptr->_Prev;
		_SCL_SECURE_VALIDATE_RANGE(this->_Ptr != _Mycont->_Myhead);

 #else /* _ITERATOR_DEBUG_LEVEL */
		this->_Ptr = this->_Ptr->_Prev;
 #endif /* _ITERATOR_DEBUG_LEVEL */

		return (*this);
		}

	_List_const_iterator operator--(int)
		{	// postdecrement
		_List_const_iterator _Tmp = *this;
		--*this;
		return (_Tmp);
		}

	bool operator==(const _List_const_iterator& _Right) const
		{	// test for iterator equality
 #if _ITERATOR_DEBUG_LEVEL == 2
		if (this->_Getcont() != _Right._Getcont())
			{	// report error
			_DEBUG_ERROR("list iterators incompatible");
			}

 #elif _ITERATOR_DEBUG_LEVEL == 1
		_SCL_SECURE_VALIDATE(this->_Getcont() == _Right._Getcont());
 #endif /* _ITERATOR_DEBUG_LEVEL */

		return (this->_Ptr == _Right._Ptr);
		}

	bool operator!=(const _List_const_iterator& _Right) const
		{	// test for iterator inequality
		return (!(*this == _Right));
		}
	};

template<class _Mylist> inline
	_List_const_iterator<_Mylist>& _Rechecked(_List_const_iterator<_Mylist>& _Iter,
		const typename _List_const_iterator<_Mylist>::_Unchecked_type _Right)
	{	// reset from unchecked iterator
	_Iter._Ptr = _Right._Ptr;
	return (_Iter);
	}

template<class _Mylist> inline
	typename _List_const_iterator<_Mylist>::_Unchecked_type _Unchecked(
		const _List_const_iterator<_Mylist>& _Iter)
	{	// make an unchecked iterator
	return (typename _List_const_iterator<_Mylist>::_Unchecked_type(_Iter._Ptr,
		static_cast<const _Mylist *>(_Iter._Getcont())));
	}

	// CLASS TEMPLATE _List_iterator
template<class _Mylist>
	class _List_iterator
		: public _List_const_iterator<_Mylist>
	{	// iterator for mutable list
public:
	using _Mybase = _List_const_iterator<_Mylist>;
	using iterator_category = bidirectional_iterator_tag;

	using _Nodeptr = typename _Mylist::_Nodeptr;
	using value_type = typename _Mylist::value_type;
	using difference_type = typename _Mylist::difference_type;
	using pointer = typename _Mylist::pointer;
	using reference = value_type&;

	_List_iterator()
		{	// construct with null node
		}

	_List_iterator(_Nodeptr _Pnode, const _Mylist *_Plist)
		: _Mybase(_Pnode, _Plist)
		{	// construct with node pointer _Pnode
		}

	using _Unchecked_type = _List_unchecked_iterator<_Mylist>;

	reference operator*() const
		{	// return designated value
		return ((reference)**(_Mybase *)this);
		}

	pointer operator->() const
		{	// return pointer to class object
		return (pointer_traits<pointer>::pointer_to(**this));
		}

	_List_iterator& operator++()
		{	// preincrement
		++(*(_Mybase *)this);
		return (*this);
		}

	_List_iterator operator++(int)
		{	// postincrement
		_List_iterator _Tmp = *this;
		++*this;
		return (_Tmp);
		}

	_List_iterator& operator--()
		{	// predecrement
		--(*(_Mybase *)this);
		return (*this);
		}

	_List_iterator operator--(int)
		{	// postdecrement
		_List_iterator _Tmp = *this;
		--*this;
		return (_Tmp);
		}
	};

template<class _Mylist> inline
	_List_iterator<_Mylist>& _Rechecked(_List_iterator<_Mylist>& _Iter,
		const typename _List_iterator<_Mylist>::_Unchecked_type _Right)
	{	// reset from unchecked iterator
	_Iter._Ptr = _Right._Ptr;
	return (_Iter);
	}

template<class _Mylist> inline
	typename _List_iterator<_Mylist>::_Unchecked_type _Unchecked(
		const _List_iterator<_Mylist>& _Iter)
	{	// make an unchecked iterator
	return (typename _List_iterator<_Mylist>::_Unchecked_type(_Iter._Ptr,
		static_cast<const _Mylist *>(_Iter._Getcont())));
	}

		// list TYPE WRAPPERS
template<class _Value_type,
	class _Size_type,
	class _Difference_type,
	class _Pointer,
	class _Const_pointer,
	class _Reference,
	class _Const_reference,
	class _Nodeptr_type>
	struct _List_iter_types
	{	// wraps types needed by iterators
	using value_type = _Value_type;
	using size_type = _Size_type;
	using difference_type = _Difference_type;
	using pointer = _Pointer;
	using const_pointer = _Const_pointer;
	using _Nodeptr = _Nodeptr_type;
	};

template<class _Value_type,
	class _Voidptr>
	struct _List_node
		{	// list node
		using _Nodeptr = _Rebind_pointer_t<_Voidptr, _List_node>;
		_Nodeptr _Next;	// successor node, or first element if head
		_Nodeptr _Prev;	// predecessor node, or last element if head
		_Value_type _Myval;	// the stored value, unused if head

		_List_node& operator=(const _List_node&) = delete;

		template<class _Alloc>
			static void _Freenode0(_Alloc& _Al, _Nodeptr _Ptr) _NOEXCEPT
			{
			using _Alnode = _Rebind_alloc_t<_Alloc, _List_node>;
			using _Alnode_traits = allocator_traits<_Alnode>;
			_Alnode _Node_alloc(_Al);
			_Alnode_traits::destroy(_Node_alloc, _STD addressof(_Ptr->_Next));
			_Alnode_traits::destroy(_Node_alloc, _STD addressof(_Ptr->_Prev));
			_Alnode_traits::deallocate(_Node_alloc, _Ptr, 1);
			}
		};

template<class _Ty>
	struct _List_simple_types
		: public _Simple_types<_Ty>
	{	// wraps types needed by iterators
	using _Node = _List_node<_Ty, void *>;
	using _Nodeptr = _Node *;
	};

template<class _Ty,
	class _Alloc>
	struct _List_base_types
	{	// types needed for a container base
	using _Alty = _Rebind_alloc_t<_Alloc, _Ty>;
	using _Alty_traits = allocator_traits<_Alty>;
	using _Node = _List_node<_Ty, typename allocator_traits<_Alloc>::void_pointer>;
	using _Alnode = _Rebind_alloc_t<_Alloc, _Node>;
	using _Alnode_traits = allocator_traits<_Alnode>;
	using _Nodeptr = typename _Alnode_traits::pointer;

	using _Val_types = conditional_t<_Is_simple_alloc_v<_Alnode>,
		_List_simple_types<_Ty>,
		_List_iter_types<_Ty,
			typename _Alty_traits::size_type,
			typename _Alty_traits::difference_type,
			typename _Alty_traits::pointer,
			typename _Alty_traits::const_pointer,
			_Ty&,
			const _Ty&,
			_Nodeptr>>;
	};

		// CLASS TEMPLATE _List_val
template<class _Val_types>
	class _List_val
		: public _Container_base
	{	// base class for list to hold data
public:
	using _Nodeptr = typename _Val_types::_Nodeptr;

	using value_type = typename _Val_types::value_type;
	using size_type = typename _Val_types::size_type;
	using difference_type = typename _Val_types::difference_type;
	using pointer = typename _Val_types::pointer;
	using const_pointer = typename _Val_types::const_pointer;
	using reference = value_type&;
	using const_reference = const value_type&;

	_List_val()
		: _Myhead(),
		_Mysize(0)
		{	// initialize data
		}

	_Nodeptr _Myhead;	// pointer to head node
	size_type _Mysize;	// number of elements
	};

		// CLASS TEMPLATE _List_alloc
template<class _Alloc_types>
	class _List_alloc
	{	// base class for list to hold allocator
public:
	using _Alnode = typename _Alloc_types::_Alnode;
	using _Alnode_traits = typename _Alloc_types::_Alnode_traits;
	using _Alproxy = _Rebind_alloc_t<_Alnode, _Container_proxy>;
	using _Alproxy_traits = allocator_traits<_Alproxy>;
	using _Node = typename _Alloc_types::_Node;
	using _Nodeptr = typename _Alloc_types::_Nodeptr;

	using _Val_types = typename _Alloc_types::_Val_types;

	using value_type = typename _Val_types::value_type;
	using size_type = typename _Val_types::size_type;
	using difference_type = typename _Val_types::difference_type;
	using pointer = typename _Val_types::pointer;
	using const_pointer = typename _Val_types::const_pointer;
	using reference = value_type&;
	using const_reference = const value_type&;

	using iterator = _List_iterator<_List_val<_Val_types>>;
	using const_iterator = _List_const_iterator<_List_val<_Val_types>>;
	using _Unchecked_iterator = _List_unchecked_iterator<_List_val<_Val_types>>;
	using _Unchecked_const_iterator = _List_unchecked_const_iterator<_List_val<_Val_types>>;

 #if _ITERATOR_DEBUG_LEVEL == 0
	_List_alloc()
		: _Mypair(_Zero_then_variadic_args_t())
		{	// default construct head node
		_Myhead() = _Buyheadnode();
		}

	template<class _Any_alloc,
		class = enable_if_t<!is_same_v<decay_t<_Any_alloc>, _List_alloc>>>
		_List_alloc(_Any_alloc&& _Al)
		: _Mypair(_One_then_variadic_args_t(),
			_STD forward<_Any_alloc>(_Al))
		{	// construct head node, allocator from _Al
		_Myhead() = _Buyheadnode();
		}

	~_List_alloc() _NOEXCEPT
		{	// destroy head node
		_Freeheadnode(_Myhead());
		}

	void _Alloc_proxy()
		{	// do nothing
		}

	void _Free_proxy()
		{	// do nothing
		}

 #else /* _ITERATOR_DEBUG_LEVEL == 0 */
	_List_alloc()
		: _Mypair(_Zero_then_variadic_args_t())
		{	// default construct head node
		_Myhead() = _Buyheadnode();
		_TRY_BEGIN
		_Alloc_proxy();
		_CATCH_ALL
		_Freeheadnode(_Myhead());
		_RERAISE;
		_CATCH_END
		}

	template<class _Any_alloc,
		class = enable_if_t<!is_same_v<decay_t<_Any_alloc>, _List_alloc>>>
		_List_alloc(_Any_alloc&& _Al)
		: _Mypair(_One_then_variadic_args_t(),
			_STD forward<_Any_alloc>(_Al))
		{	// construct head node, allocator from _Al
		_Myhead() = _Buyheadnode();
		_TRY_BEGIN
		_Alloc_proxy();
		_CATCH_ALL
		_Freeheadnode(_Myhead());
		_RERAISE;
		_CATCH_END
		}

	~_List_alloc() _NOEXCEPT
		{	// destroy proxy
		_Freeheadnode(_Myhead());
		_Free_proxy();
		}

	void _Alloc_proxy()
		{	// construct proxy
		_Alproxy _Proxy_allocator(_Getal());
		_Myproxy() = _Unfancy(_Proxy_allocator.allocate(1));
		_Alproxy_traits::construct(_Proxy_allocator, _Myproxy(), _Container_proxy());
		_Myproxy()->_Mycont = _STD addressof(_Get_data());
		}

	void _Free_proxy()
		{	// destroy proxy
		_Alproxy _Proxy_allocator(_Getal());
		_Orphan_all();
		_Alproxy_traits::destroy(_Proxy_allocator, _Myproxy());
		_Deallocate_plain(_Proxy_allocator, _Myproxy());
		_Myproxy() = 0;
		}

	_Iterator_base12 **_Getpfirst() const
		{	// get address of iterator chain
		return (_Get_data()._Getpfirst());
		}

	_Container_proxy * & _Myproxy() _NOEXCEPT
		{	// return reference to _Myproxy
		return (_Get_data()._Myproxy);
		}

	_Container_proxy * const & _Myproxy() const _NOEXCEPT
		{	// return const reference to _Myproxy
		return (_Get_data()._Myproxy);
		}
 #endif /* _ITERATOR_DEBUG_LEVEL == 0 */

	void _Copy_alloc(const _Alnode& _Al)
		{	// replace old allocator
		const bool _Reload = _Alnode_traits::propagate_on_container_copy_assignment::value
			&& _Getal() != _Al;

		if (_Reload)
			{
			_Free_proxy();
			_Freeheadnode(_Myhead());
			}

		_Pocca(_Getal(), _Al);

		if (_Reload)
			{
			_Myhead() = _Buyheadnode();
			_Alloc_proxy();
			}
		}

	void _Move_alloc(_Alnode& _Al)
		{	// replace old allocator
		const bool _Reload = _Alnode_traits::propagate_on_container_move_assignment::value
			&& _Getal() != _Al;

		if (_Reload)
			{
			_Free_proxy();
			_Freeheadnode(_Myhead());
			}

		_Pocma(_Getal(), _Al);

		if (_Reload)
			{
			_Myhead() = _Buyheadnode();
			_Alloc_proxy();
			}
		}

	_Nodeptr _Buyheadnode()
		{	// get head node using current allocator
		return (_Buynode0(_Nodeptr(), _Nodeptr()));
		}

	void _Freeheadnode(_Nodeptr _Pnode)
		{	// free head node using current allocator
		_Node::_Freenode0(_Getal(), _Pnode);
		}

	_Nodeptr _Buynode0(_Nodeptr _Next, _Nodeptr _Prev)
		{	// allocate a node and set links
		_Nodeptr _Pnode = _Getal().allocate(1);

		if (_Next == _Nodeptr())
			{	// point at self
			_Next = _Pnode;
			_Prev = _Pnode;
			}

		_Alnode& _Al = _Getal();
		_TRY_BEGIN
		_Alnode_traits::construct(_Al, _STD addressof(_Pnode->_Next), _Next);
		_Alnode_traits::construct(_Al, _STD addressof(_Pnode->_Prev), _Prev);
		_CATCH_ALL
		_Al.deallocate(_Pnode, 1);
		_RERAISE;
		_CATCH_END

		return (_Pnode);
		}

	void _Orphan_all()
		{	// orphan all iterators
		_Get_data()._Orphan_all();
		}

	void _Swap_all(_List_alloc& _Right)
		{	// swap all iterators
		_Get_data()._Swap_all(_Right._Get_data());
		}

	_Alnode& _Getal() _NOEXCEPT
		{	// return reference to allocator
		return (_Mypair._Get_first());
		}

	const _Alnode& _Getal() const _NOEXCEPT
		{	// return const reference to allocator
		return (_Mypair._Get_first());
		}

	_List_val<_Val_types>& _Get_data() _NOEXCEPT
		{	// return reference to _List_val
		return (_Mypair._Get_second());
		}

	const _List_val<_Val_types>& _Get_data() const _NOEXCEPT
		{	// return const reference to _List_val
		return (_Mypair._Get_second());
		}

	_Nodeptr& _Myhead() _NOEXCEPT
		{	// return reference to _Myhead
		return (_Get_data()._Myhead);
		}

	const _Nodeptr& _Myhead() const _NOEXCEPT
		{	// return const reference to _Myhead
		return (_Get_data()._Myhead);
		}

	size_type& _Mysize() _NOEXCEPT
		{	// return reference to _Mysize
		return (_Get_data()._Mysize);
		}

	const size_type& _Mysize() const _NOEXCEPT
		{	// return const reference to _Mysize
		return (_Get_data()._Mysize);
		}

private:
	_Compressed_pair<_Alnode, _List_val<_Val_types>> _Mypair;
	};

		// CLASS TEMPLATE _List_buy
template<class _Ty,
	class _Alloc>
	class _List_buy
		: public _List_alloc<_List_base_types<_Ty, _Alloc>>
	{	// base class for list to hold buynode/freenode functions
public:
	using _Mybase = _List_alloc<_List_base_types<_Ty, _Alloc>>;
	using typename _Mybase::_Alnode;
	using typename _Mybase::_Alnode_traits;
	using typename _Mybase::_Nodeptr;
	using typename _Mybase::_Node;

	_List_buy()
		: _Mybase()
		{	// default construct
		}

	template<class _Any_alloc,
		class = enable_if_t<!is_same_v<decay_t<_Any_alloc>, _List_buy>>>
		_List_buy(_Any_alloc&& _Al)
		: _Mybase(_STD forward<_Any_alloc>(_Al))
		{	// construct from allocator
		}

	template<class... _Valty>
		_Nodeptr _Buynode(_Nodeptr _Next, _Nodeptr _Prev, _Valty&&... _Val)
		{	// allocate a node and set links and value
		_Nodeptr _Pnode = this->_Buynode0(_Next, _Prev);
		_Alnode& _Al = this->_Getal();

		_TRY_BEGIN
		_Alnode_traits::construct(_Al,
			_STD addressof(_Pnode->_Myval),
			_STD forward<_Valty>(_Val)...);
		_CATCH_ALL
		_Al.deallocate(_Pnode, 1);
		_RERAISE;
		_CATCH_END

		return (_Pnode);
		}

	void _Freenode(_Nodeptr _Pnode)
		{	// give node back
		_Alnode& _Al = this->_Getal();
		_Alnode_traits::destroy(_Al, _STD addressof(_Pnode->_Myval));
		_Node::_Freenode0(_Al, _Pnode);
		}
	};

		// CLASS TEMPLATE list
template<class _Ty,
	class _Alloc = allocator<_Ty>>
	class list
		: public _List_buy<_Ty, _Alloc>
	{	// bidirectional linked list
public:
	static_assert(!_ENFORCE_MATCHING_ALLOCATORS || is_same_v<_Ty, typename _Alloc::value_type>,
		_MISMATCHED_ALLOCATOR_MESSAGE("list<T, Allocator>", "T"));

	using _Mybase = _List_buy<_Ty, _Alloc>;
	using _Node = typename _Mybase::_Node;
	using _Nodeptr = typename _Mybase::_Nodeptr;
	using _Alnode = typename _Mybase::_Alnode;
	using _Alnode_traits = typename _Mybase::_Alnode_traits;

	using value_type = typename _Mybase::value_type;
	using allocator_type = _Alloc;
	using size_type = typename _Mybase::size_type;
	using difference_type = typename _Mybase::difference_type;
	using pointer = typename _Mybase::pointer;
	using const_pointer = typename _Mybase::const_pointer;
	using reference = value_type&;
	using const_reference = const value_type&;

	using iterator = typename _Mybase::iterator;
	using const_iterator = typename _Mybase::const_iterator;
	using _Unchecked_iterator = typename _Mybase::_Unchecked_iterator;
	using _Unchecked_const_iterator = typename _Mybase::_Unchecked_const_iterator;

	using reverse_iterator = _STD reverse_iterator<iterator>;
	using const_reverse_iterator = _STD reverse_iterator<const_iterator>;

	list()
		: _Mybase()
		{	// construct empty list
		}

	explicit list(const _Alloc& _Al)
		: _Mybase(_Al)
		{	// construct empty list, allocator
		}

	explicit list(_CRT_GUARDOVERFLOW size_type _Count, const _Alloc& _Al = _Alloc())
		: _Mybase(_Al)
		{	// construct list from _Count * _Ty(), optional allocator
		resize(_Count);
		}

	list(_CRT_GUARDOVERFLOW size_type _Count, const _Ty& _Val)
		: _Mybase()
		{	// construct list from _Count * _Val
		_Construct_n(_Count, _Val);
		}

	list(_CRT_GUARDOVERFLOW size_type _Count, const _Ty& _Val, const _Alloc& _Al)
		: _Mybase(_Al)
		{	// construct list from _Count * _Val, allocator
		_Construct_n(_Count, _Val);
		}

	list(const list& _Right)
		: _Mybase(_Alnode_traits::select_on_container_copy_construction(_Right._Getal()))
		{	// construct list by copying _Right
		_TRY_BEGIN
		insert(begin(), _Right.begin(), _Right.end());
		_CATCH_ALL
		_Tidy();
		_RERAISE;
		_CATCH_END
		}

	list(const list& _Right, const _Alloc& _Al)
		: _Mybase(_Al)
		{	// construct list by copying _Right, allocator
		_TRY_BEGIN
		insert(begin(), _Right.begin(), _Right.end());
		_CATCH_ALL
		_Tidy();
		_RERAISE;
		_CATCH_END
		}

	template<class _Iter,
		class = enable_if_t<_Is_iterator_v<_Iter>>>
		list(_Iter _First, _Iter _Last)
		: _Mybase()
		{	// construct list from [_First, _Last)
		_Construct(_First, _Last);
		}

	template<class _Iter,
		class = enable_if_t<_Is_iterator_v<_Iter>>>
		list(_Iter _First, _Iter _Last, const _Alloc& _Al)
		: _Mybase(_Al)
		{	// construct list, allocator from [_First, _Last)
		_Construct(_First, _Last);
		}

	template<class _Iter>
		void _Construct(_Iter _First, _Iter _Last)
		{	// construct list from [_First, _Last), input iterators
		_TRY_BEGIN
		insert(begin(), _First, _Last);
		_CATCH_ALL
		_Tidy();
		_RERAISE;
		_CATCH_END
		}

	void _Construct_n(size_type _Count,
		const _Ty& _Val)
		{	// construct from _Count * _Val
		_TRY_BEGIN
		_Insert_n(_Unchecked_begin(), _Count, _Val);
		_CATCH_ALL
		_Tidy();
		_RERAISE;
		_CATCH_END
		}

	list(list&& _Right)
		: _Mybase(_STD move(_Right._Getal()))
		{	// construct list by moving _Right
		_Assign_rv(_STD move(_Right), true_type());
		}

	list(list&& _Right, const _Alloc& _Al)
		: _Mybase(_Al)
		{	// construct list by moving _Right, allocator
		_Assign_rv(_STD move(_Right), false_type());
		}

	list& operator=(list&& _Right)
		_NOEXCEPT_COND(_Alnode_traits::is_always_equal::value)
		{	// assign by moving _Right
		if (this != _STD addressof(_Right))
			{	// different, assign it
			clear();
			this->_Move_alloc(_Right._Getal());
			_Assign_rv(_STD move(_Right),
				typename _Alnode_traits::propagate_on_container_move_assignment());
			}
		return (*this);
		}

	void _Assign_rv(list&& _Right, true_type)
		{	// swap with empty *this, same allocator
		this->_Swap_all(_Right);
		_Swap_adl(this->_Myhead(), _Right._Myhead());
		_STD swap(this->_Mysize(), _Right._Mysize());
		}

	void _Assign_rv(list&& _Right, false_type)
		{	// move from _Right, possibly moving its contents
		if (this->_Getal() == _Right._Getal())
			_Assign_rv(_STD move(_Right), true_type());
		else
			_Construct(_STD make_move_iterator(_Right.begin()),
				_STD make_move_iterator(_Right.end()));
		}

	void push_front(_Ty&& _Val)
		{	// insert element at beginning
		_Insert(_Unchecked_begin(), _STD move(_Val));
		}

	void push_back(_Ty&& _Val)
		{	// insert element at end
		_Insert(_Unchecked_end(), _STD move(_Val));
		}

	iterator insert(const_iterator _Where, _Ty&& _Val)
		{	// insert _Val at _Where
		return (emplace(_Where, _STD move(_Val)));
		}

	template<class... _Valty>
		decltype(auto) emplace_front(_Valty&&... _Val)
		{	// insert element at beginning
		_Insert(_Unchecked_begin(), _STD forward<_Valty>(_Val)...);

#if _HAS_CXX17
		return (front());
#endif /* _HAS_CXX17 */
		}

	template<class... _Valty>
		decltype(auto) emplace_back(_Valty&&... _Val)
		{	// insert element at end
		_Insert(_Unchecked_end(), _STD forward<_Valty>(_Val)...);

#if _HAS_CXX17
		return (back());
#endif /* _HAS_CXX17 */
		}

	template<class... _Valty>
		iterator emplace(const_iterator _Where, _Valty&&... _Val)
		{	// insert element at _Where
 #if _ITERATOR_DEBUG_LEVEL == 2
		if (_Where._Getcont() != _STD addressof(this->_Get_data()))
			{
			_DEBUG_ERROR("list emplace iterator outside range");
			}
 #endif /* _ITERATOR_DEBUG_LEVEL == 2 */

		_Insert(_Unchecked(_Where), _STD forward<_Valty>(_Val)...);
		return (_Make_iter(--_Where));
		}

	template<class... _Valty>
		void _Insert(_Unchecked_const_iterator _Where, _Valty&&... _Val)
		{	// insert element at _Where
		const _Nodeptr _Rightnode = _Where._Ptr;
		const _Nodeptr _Leftnode = _Rightnode->_Prev;
		const _Nodeptr _Newnode = this->_Buynode(_Rightnode, _Leftnode, _STD forward<_Valty>(_Val)...);
		_Incsize(1);
		_Rightnode->_Prev = _Newnode;
		_Leftnode->_Next = _Newnode;
		}

	list(initializer_list<_Ty> _Ilist,
		const _Alloc& _Al = allocator_type())
		: _Mybase(_Al)
		{	// construct from initializer_list
		insert(begin(), _Ilist.begin(), _Ilist.end());
		}

	list& operator=(initializer_list<_Ty> _Ilist)
		{	// assign initializer_list
		assign(_Ilist.begin(), _Ilist.end());
		return (*this);
		}

	void assign(initializer_list<_Ty> _Ilist)
		{	// assign initializer_list
		assign(_Ilist.begin(), _Ilist.end());
		}

	iterator insert(const_iterator _Where,
		initializer_list<_Ty> _Ilist)
		{	// insert initializer_list
		return (insert(_Where, _Ilist.begin(), _Ilist.end()));
		}

	~list() _NOEXCEPT
		{	// destroy the object
		_Tidy();
		}

	list& operator=(const list& _Right)
		{	// assign _Right
		if (this != _STD addressof(_Right))
			{	// different, assign it
#pragma warning(push)
#pragma warning(disable: 4127)	// conditional expression is constant
			if (_Alnode_traits::propagate_on_container_copy_assignment::value
				&& this->_Getal() != _Right._Getal())
				{	// change allocator before copying
				clear();
				}
#pragma warning(pop)

			this->_Copy_alloc(_Right._Getal());

			assign(_Right.begin(), _Right.end());
			}
		return (*this);
		}

	iterator begin() _NOEXCEPT
		{	// return iterator for beginning of mutable sequence
		return (iterator(this->_Myhead()->_Next, _STD addressof(this->_Get_data())));
		}

	const_iterator begin() const _NOEXCEPT
		{	// return iterator for beginning of nonmutable sequence
		return (const_iterator(this->_Myhead()->_Next, _STD addressof(this->_Get_data())));
		}

	iterator end() _NOEXCEPT
		{	// return iterator for end of mutable sequence
		return (iterator(this->_Myhead(), _STD addressof(this->_Get_data())));
		}

	const_iterator end() const _NOEXCEPT
		{	// return iterator for end of nonmutable sequence
		return (const_iterator(this->_Myhead(), _STD addressof(this->_Get_data())));
		}

	_Unchecked_iterator _Unchecked_begin()
		{	// return iterator for beginning of mutable sequence
		return (_Unchecked_iterator(this->_Myhead()->_Next, nullptr));
		}

	_Unchecked_const_iterator _Unchecked_begin() const
		{	// return iterator for beginning of nonmutable sequence
		return (_Unchecked_const_iterator(this->_Myhead()->_Next, nullptr));
		}

	_Unchecked_iterator _Unchecked_end()
		{	// return unchecked iterator for end of mutable sequence
		return (_Unchecked_iterator(this->_Myhead(), nullptr));
		}

	_Unchecked_const_iterator _Unchecked_end() const
		{	// return unchecked iterator for end of nonmutable sequence
		return (_Unchecked_const_iterator(this->_Myhead(), nullptr));
		}

	iterator _Make_iter(const_iterator _Where) const _NOEXCEPT
		{	// make iterator from const_iterator
		return (iterator(_Where._Ptr, _STD addressof(this->_Get_data())));
		}

	iterator _Make_iter(_Unchecked_const_iterator _Where) const
		{	// make iterator from _Unchecked_const_iterator
		return (iterator(_Where._Ptr, _STD addressof(this->_Get_data())));
		}

	reverse_iterator rbegin() _NOEXCEPT
		{	// return iterator for beginning of reversed mutable sequence
		return (reverse_iterator(end()));
		}

	const_reverse_iterator rbegin() const _NOEXCEPT
		{	// return iterator for beginning of reversed nonmutable sequence
		return (const_reverse_iterator(end()));
		}

	reverse_iterator rend() _NOEXCEPT
		{	// return iterator for end of reversed mutable sequence
		return (reverse_iterator(begin()));
		}

	const_reverse_iterator rend() const _NOEXCEPT
		{	// return iterator for end of reversed nonmutable sequence
		return (const_reverse_iterator(begin()));
		}

	const_iterator cbegin() const _NOEXCEPT
		{	// return iterator for beginning of nonmutable sequence
		return (begin());
		}

	const_iterator cend() const _NOEXCEPT
		{	// return iterator for end of nonmutable sequence
		return (end());
		}

	const_reverse_iterator crbegin() const _NOEXCEPT
		{	// return iterator for beginning of reversed nonmutable sequence
		return (rbegin());
		}

	const_reverse_iterator crend() const _NOEXCEPT
		{	// return iterator for end of reversed nonmutable sequence
		return (rend());
		}

	void resize(_CRT_GUARDOVERFLOW size_type _Newsize)
		{	// determine new length, padding with _Ty() elements as needed
		if (this->_Mysize() < _Newsize)
			{	// pad to make larger
			size_type _Count = 0;
			_TRY_BEGIN
			for (; this->_Mysize() < _Newsize; ++_Count)
				_Insert(_Unchecked_end());
			_CATCH_ALL
			for (; 0 < _Count; --_Count)
				pop_back();	// undo inserts
			_RERAISE;
			_CATCH_END
			}
		else
			while (_Newsize < this->_Mysize())
				pop_back();
		}

	void resize(_CRT_GUARDOVERFLOW size_type _Newsize, const _Ty& _Val)
		{	// determine new length, padding with _Val elements as needed
		if (this->_Mysize() < _Newsize)
			_Insert_n(_Unchecked_end(), _Newsize - this->_Mysize(), _Val);
		else
			while (_Newsize < this->_Mysize())
				pop_back();
		}

	size_type size() const _NOEXCEPT
		{	// return length of sequence
		return (this->_Mysize());
		}

	size_type max_size() const _NOEXCEPT
		{	// return maximum possible length of sequence
		return (_Alnode_traits::max_size(this->_Getal()));
		}

	bool empty() const _NOEXCEPT
		{	// test if sequence is empty
		return (this->_Mysize() == 0);
		}

	allocator_type get_allocator() const _NOEXCEPT
		{	// return allocator object for values
		return (static_cast<allocator_type>(this->_Getal()));
		}

	reference front()
		{	// return first element of mutable sequence
		return (*begin());
		}

	const_reference front() const
		{	// return first element of nonmutable sequence
		return (*begin());
		}

	reference back()
		{	// return last element of mutable sequence
		return (*(--end()));
		}

	const_reference back() const
		{	// return last element of nonmutable sequence
		return (*(--end()));
		}

	void push_front(const _Ty& _Val)
		{	// insert element at beginning
		_Insert(_Unchecked_begin(), _Val);
		}

	void pop_front()
		{	// erase element at beginning
		erase(begin());
		}

	void push_back(const _Ty& _Val)
		{	// insert element at end
		_Insert(_Unchecked_end(), _Val);
		}

	void pop_back()
		{	// erase element at end
		erase(--end());
		}

	template<class _Iter,
		class = enable_if_t<_Is_iterator_v<_Iter>>>
		void assign(_Iter _First, _Iter _Last)
		{	// assign [_First, _Last), input iterators
		iterator _Old = begin();
		_TRY_BEGIN
		for (; _First != _Last && _Old != end(); ++_First, (void)++_Old)
			_Reusenode(_Old, *_First);
		for (; _First != _Last; ++_First)
			_Insert(_Unchecked_end(), *_First);
		_CATCH_ALL
		clear();
		_RERAISE;
		_CATCH_END
		erase(_Old, end());
		}

	template<class _TArg>
		void _Reusenode(iterator _Where, _TArg&& _Arg)
		{	// destroy the element at _Where and reconstruct from _Arg
		_Alnode& _Al = this->_Getal();
		_TRY_BEGIN
		_Alnode_traits::destroy(_Al, _STD addressof(_Where._Ptr->_Myval));
		_Alnode_traits::construct(_Al,
			_STD addressof(_Where._Ptr->_Myval),
			_STD forward<_TArg>(_Arg));
		_CATCH_ALL
		_Unlinknode(_Where);
		_Node::_Freenode0(_Al, _Where._Ptr);
		_RERAISE;
		_CATCH_END
		}

	void assign(_CRT_GUARDOVERFLOW size_type _Count, const _Ty& _Val)
		{	// assign _Count * _Val
		clear();
		_Insert_n(_Unchecked_begin(), _Count, _Val);
		}

	iterator insert(const_iterator _Where, const _Ty& _Val)
		{	// insert _Val at _Where
 #if _ITERATOR_DEBUG_LEVEL == 2
		if (_Where._Getcont() != _STD addressof(this->_Get_data()))
			{
			_DEBUG_ERROR("list insert iterator outside range");
			}
 #endif /* _ITERATOR_DEBUG_LEVEL == 2 */

		_Insert(_Unchecked(_Where), _Val);
		return (_Make_iter(--_Where));
		}

	iterator insert(const_iterator _Where,
		_CRT_GUARDOVERFLOW size_type _Count, const _Ty& _Val)
		{	// insert _Count * _Val at _Where
 #if _ITERATOR_DEBUG_LEVEL == 2
		if (_Where._Getcont() != _STD addressof(this->_Get_data()))
			{
			_DEBUG_ERROR("list insert iterator outside range");
			}
 #endif /* _ITERATOR_DEBUG_LEVEL == 2 */

		iterator _Prev = _Make_iter(_Where);
		if (_Prev == begin())
			{	// insert sequence at beginning
			_Insert_n(_Unchecked(_Where), _Count, _Val);
			return (begin());
			}
		else
			{	// insert sequence not at beginning
			--_Prev;
			_Insert_n(_Unchecked(_Where), _Count, _Val);
			return (++_Prev);
			}
		}

	template<class _Iter,
		class = enable_if_t<_Is_iterator_v<_Iter>>>
		iterator insert(const_iterator _Where, _Iter _First, _Iter _Last)
		{	// insert [_First, _Last) at _Where
 #if _ITERATOR_DEBUG_LEVEL == 2
		if (_Where._Getcont() != _STD addressof(this->_Get_data()))
			{
			_DEBUG_ERROR("list insert iterator outside range");
			}
 #endif /* _ITERATOR_DEBUG_LEVEL == 2 */

		iterator _Prev = _Make_iter(_Where);
		if (_Prev == begin())
			{	// insert sequence at beginning
			_Insert_range(_Unchecked(_Where), _First, _Last,
				_Iter_cat_t<_Iter>());
			return (begin());
			}
		else
			{	// insert sequence not at beginning
			--_Prev;
			_Insert_range(_Unchecked(_Where), _First, _Last,
				_Iter_cat_t<_Iter>());
			return (++_Prev);
			}
		}

	template<class _Iter>
		void _Insert_range(_Unchecked_const_iterator _Where,
			_Iter _First, _Iter _Last, input_iterator_tag)
		{	// insert [_First, _Last) at _Where, input iterators
		size_type _Num = 0;

		_TRY_BEGIN
		for (; _First != _Last; ++_First, (void)++_Num)
			_Insert(_Where, *_First);
		_CATCH_ALL
		for (; 0 < _Num; --_Num)
			{	// undo inserts
			_Unchecked_const_iterator _Before = _Where;
			_Unchecked_erase(--_Before);
			}
		_RERAISE;
		_CATCH_END
		}

	template<class _Iter>
		void _Insert_range(_Unchecked_const_iterator _Where,
			_Iter _First, _Iter _Last, forward_iterator_tag)
		{	// insert [_First, _Last) at _Where, forward iterators
		_DEBUG_RANGE(_First, _Last);
		_Iter _Next = _First;

		_TRY_BEGIN
		for (; _First != _Last; ++_First)
			_Insert(_Where, *_First);
		_CATCH_ALL
		for (; _Next != _First; ++_Next)
			{	// undo inserts
			_Unchecked_const_iterator _Before = _Where;
			_Unchecked_erase(--_Before);
			}
		_RERAISE;
		_CATCH_END
		}

	_Nodeptr _Unlinknode(const_iterator _Where)
		{	// unlink node at _Where from the list
 #if _ITERATOR_DEBUG_LEVEL == 2
		if (_Where._Getcont() != _STD addressof(this->_Get_data())
			|| _Where._Ptr == this->_Myhead())
			{
			_DEBUG_ERROR("list erase iterator outside range");
			}

		_Nodeptr _Pnode = _Where._Ptr;
		_Orphan_ptr(_Pnode);

 #else /* _ITERATOR_DEBUG_LEVEL == 2 */
		_Nodeptr _Pnode = _Where._Ptr;
 #endif /* _ITERATOR_DEBUG_LEVEL == 2 */

		_Pnode->_Prev->_Next = _Pnode->_Next;
		_Pnode->_Next->_Prev = _Pnode->_Prev;

		--this->_Mysize();
		return (_Pnode);
		}

	void _Relink(const _Unchecked_const_iterator _Where, const _Nodeptr _Ptr)
		{	// Linkup _Ptr before _Where
		_Ptr->_Next = _Where._Ptr;
		_Ptr->_Prev = _Where._Ptr->_Prev;
		_Ptr->_Prev->_Next = _Ptr;
		_Ptr->_Next->_Prev = _Ptr;

		++this->_Mysize();
		}

	iterator erase(const_iterator _Where)
		{	// erase element at _Where
		_Nodeptr _Pnode = _Unlinknode(_Where++);
		this->_Freenode(_Pnode);
		return (_Make_iter(_Where));
		}

	void _Unchecked_erase(_Unchecked_const_iterator _Where)
		{	// erase element at _Where
		_Nodeptr _Pnode = _Where._Ptr;

		_Pnode->_Prev->_Next = _Pnode->_Next;
		_Pnode->_Next->_Prev = _Pnode->_Prev;
		this->_Freenode(_Pnode);
		--this->_Mysize();
		}

	iterator erase(const_iterator _First, const_iterator _Last)
		{	// erase [_First, _Last)
		if (_First == begin() && _Last == end())
			{	// erase all and return fresh iterator
			clear();
			return (end());
			}
		else
			{	// erase subrange
			while (_First != _Last)
				_First = erase(_First);
			return (_Make_iter(_Last));
			}
		}

	void clear() _NOEXCEPT
		{	// erase all
 #if _ITERATOR_DEBUG_LEVEL == 2

		this->_Orphan_ptr(nullptr);
 #endif /* _ITERATOR_DEBUG_LEVEL == 2 */
		_Nodeptr _Pnode = this->_Myhead()->_Next;
		this->_Myhead()->_Next = this->_Myhead();
		this->_Myhead()->_Prev = this->_Myhead();
		this->_Mysize() = 0;

		for (_Nodeptr _Pnext; _Pnode != this->_Myhead(); _Pnode = _Pnext)
			{	// delete an element
			_Pnext = _Pnode->_Next;
			this->_Freenode(_Pnode);
			}
		}

	void swap(list& _Right) _NOEXCEPT // Strengthened
		{	// exchange contents with _Right
		if (this != _STD addressof(_Right))
			{	// (maybe) swap allocators, swap control information
			_Pocs(this->_Getal(), _Right._Getal());
			this->_Swap_all(_Right);
			_Swap_adl(this->_Myhead(), _Right._Myhead());
			_STD swap(this->_Mysize(), _Right._Mysize());
			}
		}

	void splice(const_iterator _Where, list& _Right)
		{	// splice all of _Right at _Where
		if (this != _STD addressof(_Right) && !_Right.empty())
			{	// worth splicing, do it
			_Splice(_Where, _Right, _Right.begin(), _Right.end(),
				_Right._Mysize());
			}
		}

	void splice(const_iterator _Where, list&& _Right)
		{	// splice all of _Right at _Where
		splice(_Where, _Right);
		}

	void splice(const_iterator _Where, list& _Right,
		const_iterator _First)
		{	// splice _Right [_First, _First + 1) at _Where
 #if _ITERATOR_DEBUG_LEVEL == 2
		if (_First == _Right.end())
			{
			_DEBUG_ERROR("list splice iterator outside range");
			}
		else

 #else /* _ITERATOR_DEBUG_LEVEL == 2 */
		if (_First != _Right.end())
 #endif /* _ITERATOR_DEBUG_LEVEL == 2 */

			{	// element exists, try splice
			const_iterator _Last = _First;
			++_Last;
			if (this != _STD addressof(_Right)
				|| (_Where != _First && _Where != _Last))
				_Splice(_Where, _Right, _First, _Last, 1);
			}
		}

	void splice(const_iterator _Where, list&& _Right,
		const_iterator _First)
		{	// splice _Right [_First, _First + 1) at _Where
		splice(_Where, _Right, _First);
		}

	void splice(const_iterator _Where,
		list& _Right, const_iterator _First, const_iterator _Last)
		{	// splice _Right [_First, _Last) at _Where
		if (_First != _Last && (this != _STD addressof(_Right) || _Where != _Last))
			{	// worth splicing, do it
			size_type _Count = 0;

			if (this == _STD addressof(_Right))
				;	// just rearrange this list
			else if (_First == _Right.begin() && _Last == _Right.end())
				_Count = _Right._Mysize();	// splice in whole list
			else
				{	// count nodes and check for knot
				const_iterator _Next = _First;

				for (; _Next != _Last; ++_Next, (void)++_Count)
					if (_Next == _Right.end())
						_Xlength_error("list<T> bad splice");
				}
			_Splice(_Where, _Right, _First, _Last, _Count);
			}
		}

	void splice(const_iterator _Where,
		list&& _Right, const_iterator _First, const_iterator _Last)
		{	// splice _Right [_First, _Last) at _Where
		splice(_Where, _Right, _First, _Last);
		}

	void remove(const _Ty& _Val)
		{	// erase each element matching _Val
		iterator _Val_it = end();

		for (iterator _First = begin(); _First != end(); )
			if (*_First == _Val)
				if (_STD addressof(*_First) == _STD addressof(_Val))
					_Val_it = _First++;
				else
					_First = erase(_First);
			else
				++_First;

		if (_Val_it != end())
			erase(_Val_it);
		}

	template<class _Pr1>
		void remove_if(_Pr1 _Pred)
		{	// erase each element satisfying _Pred
		_Remove_if(_Pred);
		}

	template<class _Pr1>
		void _Remove_if(_Pr1& _Pred)
		{	// erase each element satisfying _Pred
		for (iterator _First = begin(); _First != end(); )
			if (_Pred(*_First))
				_First = erase(_First);
			else
				++_First;
		}

	void unique()
		{	// erase each element matching previous
		unique(equal_to<>());
		}

	template<class _Pr2>
		void unique(_Pr2 _Pred)
		{	// erase each element satisfying _Pred with previous
		const _Nodeptr _Phead = this->_Myhead();
		_Nodeptr _Pprev = _Phead->_Next;
		_Nodeptr _Pnode = _Pprev->_Next;

		while (_Pnode != _Phead)
			if (_Pred(_Pprev->_Myval, _Pnode->_Myval))
				{	// match, remove it
				const _Nodeptr _Perase = _Pnode;
				_Pnode = _Pnode->_Next;

 #if _ITERATOR_DEBUG_LEVEL == 2
				_Orphan_ptr(_Perase);
 #endif /* _ITERATOR_DEBUG_LEVEL == 2 */

				_Pprev->_Next = _Pnode;
				_Pnode->_Prev = _Pprev;
				this->_Freenode(_Perase);

				--this->_Mysize();
				}
			else
				{	// no match, advance
				_Pprev = _Pnode;
				_Pnode = _Pnode->_Next;
				}
		}

	void merge(list& _Right)
		{	// merge in elements from _Right, both ordered by operator<
		_Merge1(_Right, less<>());
		}

	void merge(list&& _Right)
		{	// merge in elements from _Right, both ordered by operator<
		_Merge1(_Right, less<>());
		}

	template<class _Pr2>
		void merge(list& _Right, _Pr2 _Pred)
		{	// merge in elements from _Right, both ordered by _Pred
		_Merge1(_Right, _Pred);
		}

	template<class _Pr2>
		void merge(list&& _Right, _Pr2 _Pred)
		{	// merge in elements from _Right, both ordered by _Pred
		_Merge1(_Right, _Pred);
		}

	template<class _Pr2>
		void _Merge1(list& _Right, _Pr2&& _Pred)
		{	// merge in elements from _Right, both ordered by _Pred
		if (this != _STD addressof(_Right))
			{	// safe to merge, do it
			_DEBUG_ORDER_UNCHECKED(_Unchecked_begin(), _Unchecked_end(), _Pred);
			_DEBUG_ORDER_UNCHECKED(_Right._Unchecked_begin(), _Right._Unchecked_end(), _Pred);
			iterator _First1 = begin();
			iterator _Last1 = end();
			iterator _First2 = _Right.begin();
			iterator _Last2 = _Right.end();

			while (_First1 != _Last1 && _First2 != _Last2)
				{
				if (_Pred(*_First2, *_First1))
					{	// splice in an element from _Right
					iterator _Oldfirst2 = _First2;
					_Splice(_First1, _Right, _Oldfirst2, ++_First2, 1);
					}
				else
					{
					++_First1;
					}
				}

			if (_First2 != _Last2)
				{
				_Splice(_Last1, _Right, _First2, _Last2, _Right._Mysize());	// splice remainder of _Right
				}
			}
		}

	void sort()
		{	// order sequence, using operator<
		sort(less<>());
		}

	template<class _Pr2>
		void sort(_Pr2 _Pred)
		{	// order sequence, using _Pred
		_Sort(begin(), end(), _Pred, this->_Mysize());
		}

	template<class _Pr2>
		iterator _Sort(iterator _First, iterator _Last, _Pr2& _Pred,
			size_type _Size)
		{	// order [_First, _Last), using _Pred, return new first
			// _Size must be distance from _First to _Last
		if (_Size < 2)
			return (_First);	// nothing to do

		iterator _Mid = _STD next(_First, _Size / 2);
		_First = _Sort(_First, _Mid, _Pred, _Size / 2);
		_Mid = _Sort(_Mid, _Last, _Pred, _Size - _Size / 2);
		iterator _Newfirst = _First;

		for (bool _Initial_loop = true; ; _Initial_loop = false)
			{	// [_First, _Mid) and [_Mid, _Last) are sorted and non-empty
			if (_DEBUG_LT_PRED(_Pred, *_Mid, *_First))
				{	// consume _Mid
				if (_Initial_loop)
					_Newfirst = _Mid;	// update return value
				splice(_First, *this, _Mid++);
				if (_Mid == _Last)
					return (_Newfirst);	// exhausted [_Mid, _Last); done
				}
			else
				{	// consume _First
				++_First;
				if (_First == _Mid)
					return (_Newfirst);	// exhausted [_First, _Mid); done
				}
			}
		}

	void reverse() _NOEXCEPT
		{	// reverse sequence
		const _Nodeptr _Phead = this->_Myhead();
		_Nodeptr _Pnode = _Phead;

		for (;;)
			{	// flip pointers in a node
			const _Nodeptr _Pnext = _Pnode->_Next;
			_Pnode->_Next = _Pnode->_Prev;
			_Pnode->_Prev = _Pnext;

			if (_Pnext == _Phead)
				break;
			_Pnode = _Pnext;
			}
		}

	void _Splice(const_iterator _Where,
		list& _Right, const_iterator _First, const_iterator _Last,
		size_type _Count)
		{	// splice _Right [_First, _Last) before _Where
 #if _ITERATOR_DEBUG_LEVEL == 2
		if (_Where._Getcont() != _STD addressof(this->_Get_data()))
			{
			_DEBUG_ERROR("list splice iterator outside range");
			}

		if (this->_Getal() != _Right._Getal())
			{
			_DEBUG_ERROR("list containers incompatible for splice");
			}

		if (this != _STD addressof(_Right))
			{	// transfer ownership
			_Lockit _Lock(_LOCK_DEBUG);

			const bool _One = _Count == 1;
			const bool _All = !_One && _Count == _Right.size();
			const bool _Some = !_One && !_All;

			_Nodeptr _Oldprev = _First._Ptr->_Prev;

			if (_Some)
				for (_Nodeptr _Ptr = _First._Ptr; _Ptr != _Last._Ptr;
					_Ptr = _Ptr->_Next)
					{	// mark _Prev pointers
					_Ptr->_Prev = nullptr;
					}

			const_iterator **_Pnext = (const_iterator **)_Right._Getpfirst();

			if (_Pnext == 0)
				{
				_DEBUG_ERROR("list container corrupted");
				}

			while (*_Pnext != 0)
				{	// check the iterator
				const_iterator& _Iter = **_Pnext;

				if ((_One && _Iter._Ptr == _First._Ptr)
					|| (_All && _Iter._Ptr != _Right._Myhead())
					|| (_Some && _Iter._Ptr->_Prev == nullptr))
					{	// adopt the iterator
					*_Pnext = (const_iterator *)_Iter._Mynextiter;
					_Iter._Myproxy = this->_Myproxy();
					_Iter._Mynextiter = this->_Myproxy()->_Myfirstiter;
					this->_Myproxy()->_Myfirstiter = _STD addressof(_Iter);
					}
				else
					{	// skip the iterator
					_Pnext = (const_iterator **)_Iter._Getpnext();
					}
				}

			if (_Some)
				for (_Nodeptr _Ptr = _First._Ptr; _Ptr != _Last._Ptr;
					_Ptr = _Ptr->_Next)
					{	// restore _Prev pointers
					_Ptr->_Prev = _Oldprev;
					_Oldprev = _Ptr;
					}
			}

 #else /* _ITERATOR_DEBUG_LEVEL == 2 */
		if (this->_Getal() != _Right._Getal())
			_STD terminate();
 #endif /* _ITERATOR_DEBUG_LEVEL == 2 */

		_Splice_same(_Where, _Right, _First, _Last, _Count);
		}

	void _Splice_same(const_iterator _Where,
		list& _Right, const_iterator _First, const_iterator _Last,
		size_type _Count)
		{	// splice _Right [_First, _Last) before _Where
		if (this != _STD addressof(_Right))
			{	// splicing from another list, adjust counts
			_Incsize(_Count);
			_Right._Mysize() -= _Count;
			}

		_First._Ptr->_Prev->_Next = _Last._Ptr;
		_Last._Ptr->_Prev->_Next = _Where._Ptr;
		_Where._Ptr->_Prev->_Next = _First._Ptr;

		_Nodeptr _Pnode = _Where._Ptr->_Prev;
		_Where._Ptr->_Prev = _Last._Ptr->_Prev;
		_Last._Ptr->_Prev = _First._Ptr->_Prev;
		_First._Ptr->_Prev = _Pnode;
		}

	void _Unchecked_splice(_Unchecked_const_iterator _Where,
		_Unchecked_const_iterator _First,
		_Unchecked_const_iterator _Last)
		{	// splice [_First, _Last) before _Where
		_First._Ptr->_Prev->_Next = _Last._Ptr;
		_Last._Ptr->_Prev->_Next = _Where._Ptr;
		_Where._Ptr->_Prev->_Next = _First._Ptr;

		_Nodeptr _Pnode = _Where._Ptr->_Prev;
		_Where._Ptr->_Prev = _Last._Ptr->_Prev;
		_Last._Ptr->_Prev = _First._Ptr->_Prev;
		_First._Ptr->_Prev = _Pnode;
		}

	void _Tidy()
		{	// free all storage
		clear();
		}

	void _Insert_n(_Unchecked_const_iterator _Where,
		size_type _Count, const _Ty& _Val)
		{	// insert _Count * _Val at _Where
		size_type _Countsave = _Count;

		_TRY_BEGIN
		for (; 0 < _Count; --_Count)
			_Insert(_Where, _Val);
		_CATCH_ALL
		for (; _Count < _Countsave; ++_Count)
			{	// undo inserts
			_Unchecked_const_iterator _Before = _Where;
			_Unchecked_erase(--_Before);
			}
		_RERAISE;
		_CATCH_END
		}

	void _Incsize(size_type _Count)
		{	// alter element count, with checking
		if (max_size() - this->_Mysize() - 1 < _Count)
			_Xlength_error("list<T> too long");
		this->_Mysize() += _Count;
		}

 #if _ITERATOR_DEBUG_LEVEL == 2
	void _Orphan_ptr(_Nodeptr _Ptr)
		{	// orphan iterators with specified node pointers
		_Lockit _Lock(_LOCK_DEBUG);
		const_iterator **_Pnext = (const_iterator **)this->_Getpfirst();
		if (_Pnext != 0)
			while (*_Pnext != 0)
				{	// test an iterator
				if ((*_Pnext)->_Ptr == this->_Myhead()
					|| (_Ptr != nullptr && (*_Pnext)->_Ptr != _Ptr))
					_Pnext = (const_iterator **)(*_Pnext)->_Getpnext();
				else
					{	// orphan the iterator
					(*_Pnext)->_Clrcont();
					*_Pnext = *(const_iterator **)(*_Pnext)->_Getpnext();
					}
				}
		}
 #endif /* _ITERATOR_DEBUG_LEVEL == 2 */
	};

template<class _Ty,
	class _Alloc> inline
	void swap(list<_Ty, _Alloc>& _Left, list<_Ty, _Alloc>& _Right) _NOEXCEPT // Strengthened
	{	// swap _Left and _Right lists
	_Left.swap(_Right);
	}

template<class _Ty,
	class _Alloc> inline
	bool operator==(const list<_Ty, _Alloc>& _Left,
		const list<_Ty, _Alloc>& _Right)
	{	// test for list equality
	return (_Left.size() == _Right.size()
		&& _STD equal(_Left.begin(), _Left.end(), _Right.begin()));
	}

template<class _Ty,
	class _Alloc> inline
	bool operator!=(const list<_Ty, _Alloc>& _Left,
		const list<_Ty, _Alloc>& _Right)
	{	// test for list inequality
	return (!(_Left == _Right));
	}

template<class _Ty,
	class _Alloc> inline
	bool operator<(const list<_Ty, _Alloc>& _Left,
		const list<_Ty, _Alloc>& _Right)
	{	// test if _Left < _Right for lists
	return (_STD lexicographical_compare(_Left.begin(), _Left.end(),
		_Right.begin(), _Right.end()));
	}

template<class _Ty,
	class _Alloc> inline
	bool operator>(const list<_Ty, _Alloc>& _Left,
		const list<_Ty, _Alloc>& _Right)
	{	// test if _Left > _Right for lists
	return (_Right < _Left);
	}

template<class _Ty,
	class _Alloc> inline
	bool operator<=(const list<_Ty, _Alloc>& _Left,
		const list<_Ty, _Alloc>& _Right)
	{	// test if _Left <= _Right for lists
	return (!(_Right < _Left));
	}

template<class _Ty,
	class _Alloc> inline
	bool operator>=(const list<_Ty, _Alloc>& _Left,
		const list<_Ty, _Alloc>& _Right)
	{	// test if _Left >= _Right for lists
	return (!(_Left < _Right));
	}
_STD_END
 #pragma pop_macro("new")
 #pragma warning(pop)
 #pragma pack(pop)
#endif /* RC_INVOKED */
#endif /* _LIST_ */

/*
 * Copyright (c) by P.J. Plauger. All rights reserved.
 * Consult your license regarding permissions and restrictions.
V6.50:0009 */
