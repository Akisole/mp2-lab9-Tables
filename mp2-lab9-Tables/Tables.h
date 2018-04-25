//
// Предыдущая пара
// Базовые классы
//
#define dataCount
#define curr
#define Eff
#define arr[]
class TArrayTable {};
class TRecord {};

template <class TKey, class TVol>
class TScanTable : public TArrayTable <TKey, TVol>
{
	TScanTable (); //конструктор написать

	virtual bool Find (TKey k) {
		for (int i=0; i<dataCount; i++) {
			if (arr[i].key == k) {
				curr = i;
				return true;
			}
			Eff++;
		}
		curr = dataCount;
		return false;
	}
	virtual bool Insert (TRecord<TKey, TVol> tr) {
		if (!Find(tr.key) {
			arr[curr] = tr;
			dataCount++;
			return true;
		}
		return false;
	}
	virtual void Delete (TKey k) {
		if (Find(k)) {
			arr[curr] = arr[dataCount-1];
			dataCount--;
		}
	}
};

template <class TKey, class TVol>
class TSortTable : public TArrayTable <TKey, TVol> 
{
	TSortTable(); //конструктор написать

	virtual bool Find (TKey k) {
		int l=0, r=dataCount-1, m;
		while (l<=r) {
			Eff++;
			m=*l+r)/2;
			if(arr[m].key = k) {
				curr = m;
				return true;
			}
			if (arr[m].key < k)
				l=m+1;
			else
				r=m-1;
		}
		curr = l;
	    return false;
	}
	virtual bool Insert (TRecord<TKey, TVal> tr) {
		if(!Find(tr.key) {
			for (int i=dataCount; i>curr; i--) {
				arr[i] = arr[i-1];
				Eff++;
			}
			arr[curr] = tr;
			dataCount++;
			return true;
		}
		return false;
	}
	virtual void Delete (TKey k) {
		if(Find(k) {
			for (int i=curr; i<dataCount-1; i++) {
				arr[i] = arr[i+1];
				Eff++;
			}
			dataCount--;
		}
	}

	void Sort (int l, int r) {
		int m=(l+r)/2, i=l, j=r;
		TKey mkey = arr[m].key;
		while(i<=j) {
			Eff++;
			while (arr[i].key < mkey) {
				Eff++;
				i++;
			}
			while (arr[j].key > mkey) {
				Eff++;
				j--;
			}
			if (i <= j) {
				TKey tmp = arr[j];
				arr[j] = arr[i];
				arr[i] = tmp;
			}
		}
		if (j>l)
			Sort(l, j);
		if (i<r) 
			Sort(i, r);
	}
};
