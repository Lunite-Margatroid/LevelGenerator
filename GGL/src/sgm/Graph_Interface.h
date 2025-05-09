

namespace sgm {


	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	  // Default construction
	inline
	Graph_Interface::
	OutEdge_iterator::
	OutEdge_iterator()
	 :	data()
	{
	}

	///////////////////////////////////////////////////////////////////////////

	  // Construction by data

	inline
	Graph_Interface::
	OutEdge_iterator::
	OutEdge_iterator( const EdgeDescriptor & data_)
	 :	data( data_.clone() )
	{
	}

	///////////////////////////////////////////////////////////////////////////

	  // Destruction
	inline
	Graph_Interface::
	OutEdge_iterator::
	~OutEdge_iterator()
	{
	}

	///////////////////////////////////////////////////////////////////////////

	  // Copy construction
	  // @param toCopy the object to make this iterator a copy of
	inline
	Graph_Interface::
	OutEdge_iterator::
	OutEdge_iterator(const OutEdge_iterator & toCopy)
	 : 	data( toCopy.data.get()->clone() )
	{
	}

	///////////////////////////////////////////////////////////////////////////

	  // Assign to the given iterator
	  // @param toCopy the object to make this iterator a copy of
	inline
	Graph_Interface::
	OutEdge_iterator &
	Graph_Interface::
	OutEdge_iterator::
	operator = (const OutEdge_iterator & toCopy)
	{
		  // copy edge descriptor data
		this->data = std::unique_ptr< EdgeDescriptor >( toCopy.data.get()->clone() );
		  // access to the altered iterator
		return *this;
	}

	///////////////////////////////////////////////////////////////////////////

	  // Increment to next element
	inline
	Graph_Interface::
	OutEdge_iterator &
	Graph_Interface::
	OutEdge_iterator::
	operator ++ ()
	{
		  // proceed to next edge using the edge descriptor member function
		data.get()->operator++();
		  // access to the altered iterator
		return *this;
	}

	///////////////////////////////////////////////////////////////////////////

	  // Increment to next element
	inline
	Graph_Interface::
	OutEdge_iterator
	Graph_Interface::
	OutEdge_iterator::
	operator ++ (int)
	{
		  // create temporary copy of current state to be returned at the end
		OutEdge_iterator oldStatus(*this);
		  // proceed to next edge using the edge descriptor member function
		data.get()->operator++();
		  // access to the old non-altered iterator
		return oldStatus;
	}

	///////////////////////////////////////////////////////////////////////////

	  // access to the descriptive data of the current edge
	  // @return the current edge data
	inline
	const
	Graph_Interface::
	EdgeDescriptor&
	Graph_Interface::
	OutEdge_iterator::
	operator * () const
	{
		  // access to the dereferenced data object
		return *(data.get());
	}

	///////////////////////////////////////////////////////////////////////////

	  // access to the descriptive data of the current edge
	  // @return the current edge data
	inline
	const
	Graph_Interface::
	EdgeDescriptor* const
	Graph_Interface::
	OutEdge_iterator::
	operator -> () const
	{
		  // access to the data object
		return data.get();
	}

	///////////////////////////////////////////////////////////////////////////

	  // Equality comparison
	  // @return true if both iterators are pointing to the same edge
	inline
	bool
	Graph_Interface::
	OutEdge_iterator::
	operator == ( const OutEdge_iterator & it ) const
	{
		  // compare EdgeDescriptors
		return data.get()->operator == ( *(it.data.get()) );
	}

	///////////////////////////////////////////////////////////////////////////

	  // Inequality comparison
	  // @return true if both iterators are NOT pointing to the same edge
	inline
	bool
	Graph_Interface::
	OutEdge_iterator::
	operator != ( const OutEdge_iterator & it ) const
	{
		return ! (*this == it);
	}



	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////


	inline
	Graph_Interface::EdgeDescriptor::EdgeDescriptor()
	 : from(UINT_MAX), to(UINT_MAX)
	{}

	inline
	Graph_Interface::EdgeDescriptor::EdgeDescriptor(
			const IndexType& from_,
			const IndexType& to_ )
	 : from(from_), to(to_)
	{}

	inline
	Graph_Interface::EdgeDescriptor::~EdgeDescriptor()
	{}

	inline
	const Graph_Interface::IndexType&
	Graph_Interface::EdgeDescriptor::getFromIndex(void) const {
		return from;
	}

	inline
	const Graph_Interface::IndexType&
	Graph_Interface::EdgeDescriptor::getToIndex(void) const {
		return to;
	}


	inline
	bool
	Graph_Interface::EdgeDescriptor::operator == (const EdgeDescriptor& ed ) const {
		return ! this->operator !=(ed);
	}


	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

}  // namespace sgm

