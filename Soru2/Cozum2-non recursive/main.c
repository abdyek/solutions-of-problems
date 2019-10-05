#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
	int number;		// barındırdığı sayı, bu sorudaki xi lere karşılık gelen yer
	struct Node * back;	// geri dönüş yapmak için her düğüm nereden geldiğini unutmamalı
	struct Node * right; // sırası ile sağ, üst, sol, alt komşular
	struct Node * top;
	struct Node * left;
	struct Node * bottom;
	int index;	   // kaçıncı satır ve sütunda yer aldığını öğrenmek için sıra sayısını tutmamız gerekiyordu
	int used;	   // kullanılmış mı kullanılmamış mı kontrol etmek için, 1 (true) kullanılmış, 0 (false) kullanılmamış
};

// funcs
struct Node * createNode(int, int);    // node(düğüm) oluşturma fonksiyonu
int isAllUsed();				// bütün düğümler kullanılmış ise 1 (true) döndürecek fonksiyon
struct Node * getUnused();	// soldan sağa ve yukarıdan aşağı hareket etmek sureti ile kullanılmamış ilk düğümü getiriyor
int getRow(int);		// sıra numarası parametre olarak verilen düğümün satırını döndüren fonksiyon
int getCol(int);		// sıra numarası parametre olarak verilen düğümün sütununu döndüren fonksiyon, bu ikisi bağlama işlemi için gerekli

// global değişkenler
struct Node ** nodes;  // node işaretçi (pointer) dizisi
struct Node * buffer;  // düğüm(node)lerin geri dönüşünü tutmak için ihtiyacım olan geçici değişken
int isPrime(int);	   // parametre olarak verilen sayının asal olup olmadığını 1 ve 0 ile dönen fonksiyon
int * numbers;		   // kullanıcıdan aldığımız sayıları tuttuğumuz integer dizisi
int n;				   // satır ve sutün sayısı
int m;				   // toplam hücre sayısı (n * n)

int main() {

	scanf("%d", &n);	// ilk olarak kullanıcan kaç satır (sütun) matris gireceği hakkında bilgi alıyoruz
	m = n * n;			// m 'i de hesaplayıp m değişkenine atıyoruz
	numbers = (int *)malloc(sizeof(int) * m);	// ramden int dizi boyutu kadar yer açıyoruz, dizi tanımlama gibi düşünün
	if(n==0) {			// eğer kullanıcı 0 değeri girdiyse 0 döndürecek
		printf("0\n");
		return 0;		// kullanıcı 0 girmesi durumunda program burada bitiyor
	}
	for (int i = 0; i<m; i++) {		// toplam hücre sayısı kadar input almamız gerekiyor
		scanf("%d", &numbers[i]);
	}

	int maxSum = 0;		// en büyük değeri tutma değişkeni

	nodes = (struct Node **)malloc(sizeof(struct Node *) * m);  // hücre sayısı kadar node'a ihtiyacımız var,

	for (int i=0; i<m; i++) {		// hücre sayısı kadar düğüm (node) oluşturuyoruz ve sırası ile bu sayıları barındıracak
		// düğümlerimizi oluşturup nodes dizisine atıyoruz
		nodes[i] = createNode(numbers[i], i);
	}

	// bu while döngüsü ile bütün düğümleri right, top, left, bottom değişkenleriyle birbirine bağlıyoruz
	int ind = 0;
	while(1) {
		if((getRow(nodes[ind]->index) == 0) && (getCol(nodes[ind]->index) == 0)) {  // sol üst
			nodes[ind]->right = nodes[ind+1];
			nodes[ind]->bottom = nodes[ind+n];
			ind++;
		} else if((getRow(nodes[ind]->index) == 0) && (getCol(nodes[ind]->index) == n-1)) {  // sağ üst
			nodes[ind]->left = nodes[ind-1];
			nodes[ind]->bottom = nodes[ind+n];
			ind++;
		} else  if((getRow(nodes[ind]->index) == n-1) && (getCol(nodes[ind]->index) == 0)) {  // sol alt
			nodes[ind]->top = nodes[ind-n];
			nodes[ind]->right = nodes[ind+1];
			ind++;
		} else  if((getRow(nodes[ind]->index) == n-1) && (getCol(nodes[ind]->index) == n-1)) {  // sağ alt
			nodes[ind]->top = nodes[ind-n];
			nodes[ind]->left = nodes[ind-1];
			ind++;
		} else  if(getCol(nodes[ind]->index) == 0) {  // sol duvar
			nodes[ind]->top = nodes[ind-n];
			nodes[ind]->right = nodes[ind+1];
			nodes[ind]->bottom = nodes[ind+n];
			ind++;
		} else if(getCol(nodes[ind]->index) == n-1) { // sağ duvar
			nodes[ind]->top = nodes[ind-n];
			nodes[ind]->left = nodes[ind-1];
			nodes[ind]->bottom = nodes[ind+n];
			ind++;
		}  else if(getRow(nodes[ind]->index) == 0) { // üst duvar
			nodes[ind]->left = nodes[ind-1];
			nodes[ind]->right = nodes[ind+1];
			nodes[ind]->bottom = nodes[ind+n];
			ind++;
		}   else if(getRow(nodes[ind]->index) == n-1) { // alt duvar
			nodes[ind]->top = nodes[ind-n];
			nodes[ind]->left = nodes[ind-1];
			nodes[ind]->right = nodes[ind+1];
			ind++;
		}  else {	// others
			nodes[ind]->left = nodes[ind-1];
			nodes[ind]->top = nodes[ind-n];
			nodes[ind]->right = nodes[ind+1];
			nodes[ind]->bottom = nodes[ind+n];
			ind++;
		}
		if(ind==m) {	// index sayısı düğüm sayısına ulaşınca döngüyü kır
			break;
		}
		/*
			bu while döngüsünün bu kadar else if barındırmasının esas sebebi her düğümün sol, sağ, yukarı, aşağı komşusu olma
			zorunluluğunun olmaması. sol köşe için sadece sağ ve alt komşu vardır örneğin. Bu yüzden, köşeler ve kenarlar (duvar) 
			için istisnalar koymak zorunda kaldım
		*/
	}
	

	/*
	// burada 3*3 lük bir matrisin birbirine bağlanmasını görebilirsiniz. Neyse ki yukarıdaki while döngüsü bizim için bu
	// işi yapıyor, hatta sadece 3*3 lükleri değil kullanıcının girdiği n*n matrisler için de bunu yapıyor :)
	nodes[0]->right = nodes[1];
	nodes[0]->bottom = nodes[3];
	nodes[1]->left = nodes[0];
	nodes[1]->right = nodes[2];
	nodes[1]->bottom = nodes[4];
	nodes[2]->left = nodes[1];
	nodes[2]->bottom = nodes[5];
	nodes[3]->top = nodes[0];
	nodes[3]->right = nodes[4];
	nodes[3]->bottom = nodes[6];
	nodes[4]->right = nodes[5];
	nodes[4]->left = nodes[3];
	nodes[4]->top = nodes[1];
	nodes[4]->bottom = nodes[7];
	nodes[5]->top = nodes[2];
	nodes[5]->left = nodes[4];
	nodes[5]->bottom = nodes[8];
	nodes[6]->top = nodes[3];
	nodes[6]->right = nodes[7];
	nodes[7]->right = nodes[8];
	nodes[7]->left = nodes[6];
	nodes[7]->top = nodes[4];
	nodes[8]->left = nodes[7];
	nodes[8]->top = nodes[5];
	*/

	// kullandığım düğümleri tekrardan kullanmamak için kontrol etmem gerekir. ilk olarak kullanılmamış olarak işaretliyorum.
	// Ancak aralarında asal olanlar varsa onları işaretlemiyorum.
	// Asallar sanki burada kullanılmış sayılar gibi algılanıyor program tarafından.
	for (int i = 0; i<m; i++) {
		if(isPrime(nodes[i]->number)) {  // eğer asalsa
			nodes[i]->used = 1;			// kullanılmış olarak işaretle
		}
	}

	int sum = 0;	// o an üzerinde gezdiği adanın toplam değeri
	while(!isAllUsed()){  // bu satırın türkçesi şu: hepsi kullanılmış olmadığı sürece çalışmaya devam et
		struct Node * traveler = getUnused();	// traveler değişkenime kullanılmamış ilk düğümümü getiriyorum
		// isminden de anlaşılabileceği gibi bu gezme işlemini yapacak eleman
		while(1) {	// sonsuz döngü
			sum += traveler->number;	// sayıyı topla   *1
			// test amaçlı print, yorum satırından kaldırıp neler olduğunu görebilirsiniz
			//printf("traveler->number %d\n", traveler->number);
			//printf("sum : %d\n", sum);
			traveler->used = 1;		// bu düğümü kullandığımıza göre artık onu kullanılmış olarak işaretleyebiliriz
			if(traveler->right && !traveler->right->used) {		// eğer gezginin sağında bir düğüm varsa ve bu düğüm kullanılmamışsa
				buffer = traveler;				// geri dönüş için nereden geldiğini unutma
				traveler = traveler->right;		// sağa git
				traveler->back = buffer;		// yeni gidilen yerin back değişkenine eskisini koy
				// devam eden 3 else if bloklarında da olay bunun ile hemen hemen aynı tek fark sırası ile sol, yukarı ve aşağı yönde olmaları
			} else if(traveler->left && !traveler->left->used) {
				buffer = traveler;
				traveler = traveler->left;
				traveler->back = buffer;
			} else if(traveler->top && !traveler->top->used) {
				buffer = traveler;
				traveler = traveler->top;
				traveler->back = buffer;
			} else if(traveler->bottom && !traveler->bottom->used) {
				buffer = traveler;
				traveler = traveler->bottom;
				traveler->back = buffer;
			} else if(traveler->back) { // bir düğümün solunda, sağında, yukarısında ve aşağısında bir düğüm yoksa ya da kullanılmışsa
				// artık geri dönme vakti gelmiştir tabi eğer varsa
				traveler = traveler->back; // geri dönme işlemi
				// test amaçlı print, yorum satırından kaldırıp neler olduğunu görebilirsiniz
				//printf("back number %d\n", traveler->number);
				sum -= traveler->number;  // yukarıda toplama işlemini tekrar yapacağı için değerini çıkarıyorum *1 ile işaretli yer
			} else { // bir düğümün solunda, sağında, yukarısında, aşağısında ve gerisinde düğüm yoksa ya da kullanılmışsa ada turu tamamlanmıştır
				if(sum>maxSum) {  // gezilen adanın değeri maxSum değişkeninden büyük ise bu sayıyı tut
					maxSum = sum;
				}
				break;  // artık döngüyü kırma zamanı çünkü ada turu bitti
			}
		}
		sum = 0;   // varsa yeni ada gezisi yapacağımız için sum'ı sıfırlıyorum çünkü sum o an üzerinde gezindiğimiz adanın değerini tutuyordu
	}

	printf("%d\n", maxSum);  // artık en büyüğü yazdırabiliriz

	return 0;
}


struct Node * createNode(int number, int index) {  // düğüm oluşturuyoruz, ilk değer tuttuğu sayı ikincisi nodes dizisindeki sıra sayısı
	// bu sıra sayısını kaçıncı satırda ve sutünde yer aldığını bulmak için kullanıyoruz
	struct Node * node = (struct Node *)malloc(sizeof(struct Node));	// bellekten yer açma işlemi
	node->number = number;
	node->back = NULL;
	node->right = NULL;
	node->top   = NULL;
	node->left = NULL;
	node->bottom = NULL;
	node->index = index;
	node->used = 0;		// varsayılan olarak kullanılmamış olarak işaretli
	// ^ değerleri atıyorum
	return node;	// geriye oluşturduğumuz düğümü dönüyoruz
}

int isAllUsed() { // nodes dizisindeki bütün düğümler kullanılmış mı onu kontrol eden fonksiyon, while için gerekli
	int control = 1;
	for (int i=0; i<m; i++) {
		if(nodes[i]->used==0) {
			control = 0;
		}
	}
	return control;
}

int isPrime(int number) {
	if(number < 2) {	// 2 en küçük asal sayıdır, eğer sayı 2 den küçükse false döndür
		return 0;
	}
	for (int dividing = 2; dividing<number; dividing++) {  // 2 den sayıya kadar bölme işlemi yapıyoruz eğer birisinin modu 0 ise
		// bu o sayının asal olmadığı anlamına gelir ve uzatmadan geriye false dönmeli
		if(number%dividing==0) {
			return 0;
		}
	}
	return 1;  // iki durumdan da sorunsuz geçiş yaptıysa bu sayı asaldır geriye true dönmeli
}

struct Node * getUnused() {  // nodes dizisindeki kullanılmamış ilk düğümü getiren fonksiyon
	for(int i=0;i<m;i++) {
		if(nodes[i]->used==0) {
			return nodes[i];
		}
	}
}

// getCol ve getRow düğümün nodes dizisi içindeki sıra numarasını verdiğimizde bize satır ve sütun numarasını döndüren fonksiyonlar
// left, top, right, bottom değişkenleri ile birbirine bağlama işlemi için buna ihtiyacım vardı
int getCol(int index) {
	return index % n;
}
int getRow(int index) {
	return (int)index/n;
}

