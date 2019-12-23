#include <iostream>
#include <conio.h>
#include <cstdlib>

using namespace std;

class simpul_SBBST{
	
	public:
		int tinggi, data;
		simpul_SBBST*kiri, *kanan;
		
		simpul_SBBST(){
			kiri = NULL;
			kanan = NULL;
			data = 0;
			tinggi = 0;
		}
		
		simpul_SBBST(int n){
			kiri = NULL;
			kanan = NULL;
			data = n;
			tinggi = 0;
		}
};

class pohonbstseimbang{
	private :
		simpul_SBBST*akar;
	public:
		pohonbstseimbang(){
			akar = NULL;
		}
		bool apakosong(){
			return akar == NULL;
		}
		
	void membuatkosong(){
		akar = NULL;
	}
	
	void sisip(int data){
		akar = sisip(data,akar);
	}
	
	int tinggi (simpul_SBBST*t){
		return t == NULL ? -1 :t->tinggi;
	}
	
	int maks (int ihs, int rhs){
		return ihs > rhs ? ihs :rhs;
	}
	
	simpul_SBBST*sisip(int x,simpul_SBBST*t){
		if(t==NULL)
			t = new simpul_SBBST(x);
		else if(x<t->data){
			t->kiri = sisip(x,t->kiri);
			
			if(tinggi(t->kiri)-tinggi(t->kanan)==2)
				if(x<t->kiri->data)
				t = rotasidengananakkiri(t);
				else
				t = doubledengananakkiri(t);
		}
		else if (x>t->data){
			t->kanan = sisip(x,t->kanan);
			if(tinggi(t->kanan)-tinggi(t->kiri)==2)
				if(x>t->kanan->data)
					t = rotasidengananakkanan(t);
				else
					t = doubledengananakkanan(t);
		}
		t->tinggi = maks(tinggi(t->kiri),tinggi(t->kanan))+1;
		return t;
	}
	
	simpul_SBBST*rotasidengananakkiri(simpul_SBBST*k2){
		simpul_SBBST*k1 = k2->kiri;
		k2->kiri = k2->kanan;
		k1->kanan = k2;
		k2->tinggi = maks(tinggi(k2->kiri),tinggi(k2->kanan))+1;
		k1->tinggi = maks(tinggi(k1->kanan),k2->tinggi)+1;
		return k1;
	}
	simpul_SBBST*rotasidengananakkanan(simpul_SBBST*k1){
		simpul_SBBST*k2 = k1->kanan;
		k1->kanan = k2->kiri;
		k2->kanan = k1;
		k1->tinggi = maks(tinggi(k1->kiri),tinggi(k1->kanan))+1;
		k2->tinggi = maks(tinggi(k2->kanan),k1->tinggi)+1;
		return k2;
	}
	simpul_SBBST*doubledengananakkiri(simpul_SBBST*k3){
		k3->kiri = rotasidengananakkanan(k3->kiri);
		return rotasidengananakkiri(k3);
	}
	
	simpul_SBBST*doubledengananakkanan(simpul_SBBST*k1){
		k1->kanan = rotasidengananakkiri(k1->kanan);
		return rotasidengananakkanan(k1);
	}
	int hitungsimpul(){
		return hitungsimpul(akar);
	}
	
	int hitungsimpul (simpul_SBBST*r){
		if(r==NULL)
		return 0;
		else{
			int i=1;
			i+=hitungsimpul(r->kiri);
			i+=hitungsimpul(r->kanan);
			return i;
		}
	}
	bool cari(int nil){
		return cari(akar,nil);
	}
	bool cari(simpul_SBBST*r, int nil){
		bool ditemukan = false;
		while((r!=NULL)&&!ditemukan){
			
			int nilaikanan = r->data;
			if(nil<nilaikanan)
				r=r->kiri;
			else if(nil>nilaikanan)
				r=r->kanan;
			else{
				ditemukan = true;
				break;
			}
			ditemukan = cari(r,nil);
		}
		return ditemukan;
	}
	
	void inorder(){
		inorder(akar);
	}
	void inorder(simpul_SBBST*r){
		if(r!=NULL){
			inorder(r->kiri);
			cout<<r->data<<" ";
			inorder(r->kanan);
		}
	}
	void preorder(){
		preorder(akar);
	}
	void preorder(simpul_SBBST*r){
		if(r!=NULL){
			cout<<r->data<<" ";
			preorder(r->kiri);
			preorder(r->kanan);
		}
	}
	void postorder(){
		postorder(akar);
	}
	void postorder(simpul_SBBST*r){
			if(r!=NULL){
			postorder(r->kiri);
			postorder(r->kanan);
			cout<<r->data<<" ";
		}
	}
};

int main(){
	pohonbstseimbang sbbst;
	cout<<"uji pohon BST Seimbang\n";
	int nil;
	char ch;
	
	do{
		cout<<"\nOperasi-Operasi Pohon BST Seimbang\n";
		cout<<"1. Sisip"<<endl;
		cout<<"2. Hitung Simpul"<<endl;
		cout<<"3. Cari"<<endl;
		cout<<"4. Periksa Kosong"<<endl;
		cout<<"5. Membuat Kosong"<<endl;
		
		int pilihan;
		cout<<" Masukan Pilihan Anda : ";
		cin>>pilihan;
		
		switch(pilihan){
			
			case 1:
				cout<<" Masukan elemen Integer yang akan disisipkan : ";
				cin>>nil;
				sbbst.sisip(nil);
				break;
				
			case 2:
				cout<<" Simpul = "<<sbbst.hitungsimpul()<<endl;
				break;
				
			case 3:
				cout<<" Masukan elemen integer yang akan dicari : ";
				cin>>nil;
				
				if(sbbst.cari(nil))
					cout<<nil<<"ditemukan didalam pohon "<<endl;
				else
					cout<<nil<<"tidak ditemukan"<<endl;
					break;
					
			case 4:
				cout<<" Status Kosong = ";
				if(sbbst.apakosong())
					cout<<"Pohon Kosong"<<endl;
				else
					cout<<"Pohon Tidak Kosong"<<endl;
				break;
				
			case 5:
				cout<<"\nPohon dikosongkan\n";
				sbbst.membuatkosong();
				break;
				
			default:
				cout<<"Entry salah \n";
				break;
		}
		
		cout<<"\n Post Order : ";
		sbbst.postorder();
		cout<<"\n Pre Order : ";
		sbbst.preorder();
		cout<<"\n In Order : ";
		sbbst.inorder();
		cout<<"\nAnda ingin melanjutkan (ketik y atau t): ";
		cin>>ch;
	}
	while(ch=='Y'||ch=='y');
	
		getch();
		return 0;
}
