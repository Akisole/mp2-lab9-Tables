
template <class T>
class TStack {
	int maxsize;		//Размер стека
	int size;			//Число элементов в стеке
	T* array;	
public:
	TStack<T> (int _msize) {
		if (_msize<0)
			throw -1;
		array=new T[_msize];
		maxsize=_msize;
		size=0;
	}
	~TStack<T>() {
		delete[] array;
	}
	TStack<T> (const TStack<T>& TS) {
		size=TS.size;
		maxsize=TS.maxsize;
		array=new T[maxsize];
		for (int i=0; i<size; i++)
			array[i]=TS.array[i];
	}
	TStack<T>& operator=(const TStack& TS) {
		if(this!=&TS) {
			if(maxsize!=TS.maxsize) {
				delete[] array;
				maxsize=TS.maxsize;
				array=new T[maxsize];
			}
			size=TS.size;
			for(int i=0; i<size; i++)
				array[i]=TS.array[i];
		}
		return (*this);
	}

	//Проверка на переполнение
	int IsFull()			
	{
		if(size==maxsize)
			return 1;
		else
			return 0;
	}
	//Проверка на пустоту
	int IsEmpty()			
	{
		if(size==0)
			return 1;
		else 
			return 0;
	}
	//Посмотреть последний элемент стека
	T Top()					
	{
		if(IsEmpty())
			throw -1;
		return array[size-1];
	}
	//Достать элемент из стека
	T Pop()					
	{
		if(IsEmpty())
			throw -1;
		size--;
		return array[size];
	}
	//Добавить элемент в стек
	void Push(const T& el){
		if(IsFull())
			throw -1;
		array[size]=el;
		size++;

	} 
	//Очистить стек
	void Clear() {
		size=0;
	}
};
