#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include <sstream>
#include<fstream>
#include <cstring>
#include<exception>
#include<exception>
#include<map>
#include<set>
#include<vector>
#include<list>
#include <chrono>
#include <ctime>
using namespace std;

class Showroom {
private:


	static string denumire;
	const int id;
	char* adresa;
	int nr_masini_disponibile;
	int capacitate;
public:
	//constructor default
	Showroom(int id) :id(id) {
		this->adresa = new char[strlen("Necunoscuta") + 1];
		strcpy(this->adresa, "Necunoscuta");
		this->nr_masini_disponibile = 0;
		this->capacitate = 0;
	}



	//write to binary file

	void writeTOFile(fstream& s) {

		//pt int

		s.write((char*)&this->id, sizeof(int));
		//char*
		int lungime = strlen(this->adresa + 1);
		s.write((char*)&lungime, sizeof(lungime));
		s.write(this->adresa, lungime);
		//pt int
		s.write((char*)&this->nr_masini_disponibile, sizeof(int));
		s.write((char*)&this->capacitate, sizeof(int));


	}

	//read from 
	void readFromFile(fstream& s) {
		//pt int
		s.read((char*)&this->id, sizeof(int));

		//pt char*

		int adresaLength;
		s.read((char*)&adresaLength, sizeof(int));
		char* adresa = new char[adresaLength + 1];
		s.read(adresa, adresaLength);


		//pt int
		s.read((char*)&this->nr_masini_disponibile, sizeof(int));
		s.read((char*)&this->capacitate, sizeof(int));

	}
	/*//write to binary file

	void writeTOFile(fstream& s) {
		//char*
		s.write((char*)&this->adresa, sizeof(char*));
		//int
		s.write((char*)&this->capacitate, sizeof(int));
		s.write((char*)&this->nr_masini_disponibile, sizeof(int));
	}

	//read from */




	//constructor cu toti parametrii
	Showroom(int id, const char* adresa, int capacitate, int nr_masini_disponibile) :id(id)
	{

		this->adresa = new char[strlen(adresa) + 1];
		strcpy(this->adresa, adresa);

		if (capacitate > 0)
			this->capacitate = capacitate;
		else
			throw new exception("Nu Showroom-ul nu poate avea 0 masini disponibile");

		if (nr_masini_disponibile <= capacitate)
			this->nr_masini_disponibile = nr_masini_disponibile;
		else
			throw new exception("Nu pot fi introduse mai multe masini decat capacitatea showroom-ului");
	}

	//destructor
	~Showroom() {
		if (this->adresa != nullptr)
			delete this->adresa;
	}
	//constructor de copiere
	Showroom(const Showroom& s) :id(s.id) {
		this->adresa = new char[strlen(s.adresa) + 1];
		strcpy(this->adresa, s.adresa);

		if (s.capacitate > 0)
			this->capacitate = s.capacitate;
		else
			throw new exception("Nu Showroom-ul nu poate avea 0 masini disponibile");

		if (s.nr_masini_disponibile <= s.capacitate)
			this->nr_masini_disponibile = s.nr_masini_disponibile;
		else
			throw new exception("Nu pot fi introduse mai multe masini decat capacitatea showroom-ului");
	}

	//operator =
	Showroom& operator =(const Showroom& s) {
		if (this != &s) {
			//destructor
			if (this->adresa != nullptr)
				delete this->adresa;
			//constructor de copiere
			this->adresa = new char[strlen(s.adresa) + 1];
			strcpy(this->adresa, s.adresa);
			this->capacitate = s.capacitate;
			this->nr_masini_disponibile = s.nr_masini_disponibile;
		}
		return *this;
	}

	//getteri
	char* getadresa() const {
		return this->adresa;
	}
	static string getdenumirea() {
		return denumire;
	}
	int getid() const {
		return this->id;
	}
	int getmasini_disponibile() const {
		return this->nr_masini_disponibile;
	}
	int getcapacitate() const {
		return this->capacitate;
	}
	//setteri
	void setadresa(const char* adresa) {
		if (this->adresa != nullptr) {
			delete[]this->adresa;
		}
		this->adresa = new char[strlen(adresa) + 1];
		strcpy(this->adresa, adresa);
	}

	void setcapacite(int capacitate) {
		if (capacitate > 0) {
			this->capacitate = capacitate;
		}
	}
	void setmasini_disponibile(int disponibilitate) {
		if (disponibilitate <= this->capacitate) {
			this->nr_masini_disponibile = disponibilitate;
		}
	}
	//ostream
	friend ostream& operator <<(ostream& out, const Showroom& s) {
		out << endl;
		out << "-----------------Showroom-----------------" << endl;
		out << "\nNumele Showroomului de masini este : " << s.denumire;
		out << "\nId-ul este : " << s.id;
		out << "\nAdresa este : " << s.adresa;
		out << "\nCapacitatea este de " << s.capacitate << " de masini";
		out << "\nNumarul masinilor disponibile este : " << s.nr_masini_disponibile;
		out << endl;
		return out;
	}
	//istream
	friend istream& operator>>(istream& in, Showroom& s) {
		delete[]s.adresa;
		cout << endl;
		cout << "\n-----------------Showroom-----------------";
		cout << "\nAdresa este : ";
		char aux[100];
		in.getline(aux, 99);
		s.adresa = new char[strlen(aux) + 1];
		strcpy(s.adresa, aux);
		cout << "\nCapacitatea este de : ";
		in >> s.capacitate;
		cout << "\nNumarul masinilor disponibile este : ";
		in >> s.nr_masini_disponibile;
		return in;
	}
	//operator ++pre-incrrementare
	Showroom& operator++() {
		if (this->nr_masini_disponibile < this->capacitate) {
			this->nr_masini_disponibile++;
		}
		else cout << "Nu poate fi marit numarul de masini deoarece depaseste capacitatea";
		return *this;
	}
	//operator ++post-incrementare
	Showroom& operator++(int) {
		Showroom copie = *this;
		if (this->nr_masini_disponibile < this->capacitate) {
			this->nr_masini_disponibile++;
		}
		else cout << "Nu poate fi marit numarul de masini deoarece depaseste capacitatea";
		return copie;
	}
	//operator cast explicit
	explicit operator float() {
		return this->capacitate;
	}
	//operator >
	bool operator < (int capacitatea) {
		return this->nr_masini_disponibile < capacitatea;
	}
	//operator !
	bool operator!() {
		return capacitate > 0;
	}
	//operator +=
	void operator +=(int x) {
		this->capacitate += x;
	}
	//Numarul locurilor disponibile
	void Loc_diponibil() {
		cout << "\nNumarul locurilor libere este de " << this->capacitate - this->nr_masini_disponibile;
	}
	// de intrebat
//operator ==
	bool operator==(Showroom& s) {
		if (this->id == s.id)
			return true;
	}
};

string Showroom::denumire = "Autovit";

class Masina {
private:
	static int contor;
	const int id;
	string marca;
	char* model;
	int an_fabricatie;
	int nr_revizii;
	float* pret_revizii;
	float pret;
public:

	//fisier binar
	/*void writeTOFile(fstream& m) {
	 //string
		int lg = this->marca.length() + 1;
		m.write((char*)&lg, sizeof(int));
		m.write(this->marca.data(), lg * sizeof(char));
		//char*
		m.write((char*)&this->model, sizeof(char*));
		//int
		m.write((char*)&this->an_fabricatie, sizeof(int));
		m.write((char*)&this->nr_revizii, sizeof(int));
		//float*
		for (int i = 0; i < this->nr_revizii; i++)
		{
			m.write((char*)&pret_revizii[i], sizeof(pret_revizii[i]));
		}
		//float
		m.write((char*)&this->pret, sizeof(float));
	}*/

	//operator indexare
	float& operator[](int index) {
		if (index >= 0 && index <= this->nr_revizii) {
			return this->pret_revizii[index];
		}
		else cout << "\nNu exista plata cu numarul " << index;
	}

	//operator+=
	Masina operator+=(float plata) {
		Masina copie = *this;
		delete[]this->pret_revizii;
		this->nr_revizii++;
		this->pret_revizii = new float[this->nr_revizii];
		for (int i = 0; i < copie.nr_revizii; i++) {
			this->pret_revizii[i] = copie.pret_revizii[i];
		}
		this->pret_revizii[this->nr_revizii - 1] = plata;
		return *this;
	}
	//operator++ pre-incrementare
	Masina& operator++() {
		this->pret++;
		return *this;
	}

	//operator++ pre-incrementare
	Masina& operator++(int) {
		Masina copie = *this;
		this->pret++;
		return copie;
	}
	//operator cast
	explicit operator int() {
		return this->pret;
	}

	//bool>
	bool operator>(Masina& m) {
		return this->pret > m.pret;
	}

	bool operator>(int pret) {
		return this->pret > pret;
	}
	//constructor default
	Masina() :id(++contor) {
		this->marca = "Necunoscuta";
		this->model = new char[strlen("Necunoscut") + 1];
		strcpy(this->model, "Necunoscut");
		this->an_fabricatie = 0;
		this->nr_revizii = 0;
		this->pret_revizii = nullptr;
		this->pret = 0;
	}
	//constructor cu toti parametrii
	Masina(string marca, const char* model, int an_fabricatie, int nr_revizii, float* pret_revizii, float pret) :id(++contor) {
		this->marca = marca;
		this->model = new char[strlen(model) + 1];
		strcpy(this->model, model);
		if (an_fabricatie >= 1800)
			this->an_fabricatie = an_fabricatie;
		else throw new exception("Nu poat exista masini fabricate inainte de 1800");
		this->nr_revizii = nr_revizii;
		this->pret_revizii = new float[this->nr_revizii];
		for (int i = 0; i < nr_revizii; i++) {
			this->pret_revizii[i] = pret_revizii[i];
		}
		if (pret > 0)
			this->pret = pret;
		else throw new exception("Pretul masinii nu poate fi 0 sau mai mic decat 0");

	}
	//destructor
	~Masina() {
		if (this->model != nullptr)
			delete[]this->model;
		if (this->pret_revizii != nullptr) {
			delete[]this->pret_revizii;
		}
	}

	//constructor de copiere

	Masina(const Masina& m) : id(m.id) {
		//this->contor--;
		this->marca = m.marca;
		this->model = new char[strlen(m.model) + 1];
		strcpy(this->model, m.model);
		this->an_fabricatie = m.an_fabricatie;
		this->nr_revizii = m.nr_revizii;
		this->pret_revizii = new float[this->nr_revizii];
		for (int i = 0; i < this->nr_revizii; i++) {
			this->pret_revizii[i] = m.pret_revizii[i];
		}
		this->pret = m.pret;
	}

	//operator =
	Masina& operator=(const Masina& m) {
		if (this != &m) {
			//destructor
			if (this->model != nullptr)
				delete[]this->model;
			if (this->pret_revizii != nullptr) {
				delete[]this->pret_revizii;
			}
			//constructor de copiere
			this->marca = m.marca;
			this->model = new char[strlen(m.model) + 1];
			strcpy(this->model, m.model);
			this->an_fabricatie = m.an_fabricatie;
			this->nr_revizii = m.nr_revizii;
			this->pret_revizii = new float[this->nr_revizii];
			for (int i = 0; i < this->nr_revizii; i++) {
				this->pret_revizii[i] = m.pret_revizii[i];
			}
			this->pret = m.pret;
		}
		return *this;
	}

	//getter
	int getid() {
		return this->id;
	}

	string getMarca() {
		return this->marca;
	}
	char* getModel() {
		return this->model;
	}
	int getAn_fabricatie() {
		return this->an_fabricatie;
	}
	int getNr_revizii() {
		return this->nr_revizii;
	}
	float* getPret_revizii() {
		return this->pret_revizii;
	}
	float getPret() {
		return this->pret;
	}
	//setteri
	void setMarca(string marca) {
		this->marca = marca;
	}
	void setModel(const char* model) {
		delete[]this->model;
		if (strlen(model) >= 1) {
			this->model = new char[strlen(model) + 1];
			strcpy(this->model, model);
		}
	}
	void setAn_fabricatie(int an_fabricatie) {
		if (an_fabricatie >= 1800)
			this->an_fabricatie = an_fabricatie;
	}
	void setPret_revizii(int nr_revizii, float* pret_revizii) {
		delete[]this->pret_revizii;
		if (nr_revizii > 0) {
			this->nr_revizii = nr_revizii;
			this->pret_revizii = new float[this->nr_revizii];
			for (int i = 0; i < this->nr_revizii; i++)
				this->pret_revizii[i] = pret_revizii[i];
		}
		else
			cout << "Nu are revizii anterioare";
	}
	void setPret(float pret) {
		this->pret = pret;
	}

	//ostream
	friend ostream& operator<<(ostream& out, const Masina& m) {
		out << endl;
		out << "\n-------------------Masina--------------------";
		out << "\nId-ul este : " << m.id;
		out << "\nMarca masinii este : " << m.marca;
		out << "\nModel : " << m.model;
		out << "\nAn fabricatie : " << m.an_fabricatie;
		out << "\nNumarul reviziilor : " << m.nr_revizii;
		out << "\nPreturile reviziilor : ";
		for (int i = 0; i < m.nr_revizii; i++) {
			out << m.pret_revizii[i] << " ";
		}
		out << "\nPretul : " << m.pret << " euro";
		return out;
	}
	//istream 
	friend istream& operator>>(istream& in, Masina& m) {
		cout << endl;
		cout << "\n-------------------Masina--------------------";
		delete[]m.model;
		delete[]m.pret_revizii;
		cout << "\nMarca este : ";
		in >> m.marca;
		in.ignore();
		cout << "\nModelul este : ";
		char aux[100];
		in.getline(aux, 99);
		m.model = new char[strlen(aux) + 1];
		strcpy(m.model, aux);
		cout << "\nAnul este : ";
		in >> m.an_fabricatie;
		cout << "\nNumarul reviziilor  este : ";
		in >> m.nr_revizii;
		cout << "\nPreturile reviziilor : ";
		m.pret_revizii = new float[m.nr_revizii];
		for (int i = 0; i < m.nr_revizii; i++) {
			in >> m.pret_revizii[i];
		}
		cout << "\nPret masina: ";
		in >> m.pret;
		return in;
	}
	//meniu

 //fisier binar 
	void writeToFile(fstream& m) {
		//pt int 
		m.write((char*)&this->id, sizeof(int));
		//pt string
		int lg = this->marca.length() + 1;
		m.write((char*)&lg, sizeof(int));
		m.write(this->marca.data(), lg * sizeof(char));
		//pt char*

		lg = strlen(this->model + 1);
		m.write((char*)&lg, sizeof(lg));
		m.write(this->model, lg);
		//pt int
		m.write((char*)&this->an_fabricatie, sizeof(int));
		//pt int
		m.write((char*)&this->nr_revizii, sizeof(int));
		//float *
		for (int i = 0; i < this->nr_revizii; i++) {
			m.write((char*)&this->pret_revizii[i], sizeof(pret_revizii[i]));
		}
		//pt float singur
		m.write((char*)&this->pret, sizeof(float));
	}


	void readFromFile(fstream& m) {
		//pt int
		m.read((char*)&this->id, sizeof(int));
		//pt string
		int lg;
		m.read((char*)&lg, sizeof(int));
		char* buffer = new char[lg];
		m.read(buffer, lg);
		this->marca = buffer;
		delete[]buffer;
		//pt char*
		m.read((char*)&lg, sizeof(int));
		char* model = new char[lg + 1];
		m.read(this->model, lg);
		//pt int
		m.read((char*)&this->an_fabricatie, sizeof(int));
		//pt int
		m.read((char*)&this->nr_revizii, sizeof(int));
		//pt float *
		delete[] pret_revizii;
		this->pret_revizii = new float[this->nr_revizii];
		for (int i = 0; i < this->nr_revizii; i++) {
			m.read((char*)&pret_revizii[i], sizeof(pret_revizii[i]));
		}
		//float
		m.read((char*)&this->pret, sizeof(float));
	}

	friend bool operator<(const Masina& m1, const Masina& m2)
	{
		if (m1.id < m2.id)
			return true;
		return false;
	}

	bool operator()(const Masina& lhs, const Masina& rhs) const {
		// Define the comparison criteria for Masina objects
		// For example, you can compare based on the id
		return lhs.id == rhs.id;
	}

};

int Masina::contor = 0;

class Furnizor {
private:
	static float TVA;
	const int id;
	char* nume_firma;
	float pret_initial;
	float pret_final;
	bool platita;
	float suma_platita;
	int nr_rate;
	//rata pe luna
public:

	//fisier binar

	void writeTOFile(fstream& f) {
		f.write((char*)&this->nume_firma, sizeof(char*));
		//float
		f.write((char*)&this->pret_initial, sizeof(float));
		//bool
		f.write((char*)&this->platita, sizeof(platita));
		//int
		f.write((char*)&this->suma_platita, sizeof(float));
		f.write((char*)&this->nr_rate, sizeof(int));

	}

	//constructor default
	Furnizor(int id) :id(id) {
		this->nume_firma = new char[strlen("Necunoscut") + 1];
		strcpy(this->nume_firma, "Necunoscut");
		this->pret_initial = 0;
		this->pret_final = 0;
		this->platita = false;
		this->suma_platita = 0;
		this->nr_rate = 0;
	}
	/*Furnizor(int id) :id(id) {
		this->nume_firma = new char[strlen("Necunoscut") + 1];
		strcpy(this->nume_firma, "Necunoscut");
		this->pret_initial = 0;
		this->pret_final = 0;
		this->platita = false;}*/


		//constructor cu toti parametrii

	Furnizor(int id, const char* nume_firma, float pret_initial, bool platita, float suma_platita, int nr_rate) :id(id) {
		this->nume_firma = new char[strlen(nume_firma) + 1];
		strcpy(this->nume_firma, nume_firma);
		if (pret_initial > 0) {
			this->pret_initial = pret_initial;
		}
		else throw new exception("Pretul de fabrica al masinii nu poate fi 0");
		this->platita = platita;
		if (this->platita == false) {
			if (suma_platita <= pret_initial)
			{
				this->suma_platita = suma_platita;
				this->nr_rate = nr_rate;
			}
		}
		else {
			this->suma_platita = 0;
			this->nr_rate = 0;
		}
	}

	//destructor
	~Furnizor() {
		delete[]this->nume_firma;
	}

	//constructor de copiere
	Furnizor(const Furnizor& f) :id(f.id) {
		this->nume_firma = new char[strlen(f.nume_firma) + 1];
		strcpy(this->nume_firma, f.nume_firma);
		this->pret_initial = f.pret_initial;
		this->platita = f.platita;
		if (this->platita = false) {
			if (f.suma_platita <= f.pret_initial)
				this->suma_platita = f.suma_platita;
			this->nr_rate = f.nr_rate;
		}
	}

	//operator =
	Furnizor& operator=(const Furnizor& f) {
		if (this != &f) {
			//destructor
			delete[]this->nume_firma;
			//constructor de copiere
			this->nume_firma = new char[strlen(f.nume_firma) + 1];
			strcpy(this->nume_firma, f.nume_firma);
			this->pret_initial = f.pret_initial;
			this->platita = f.platita;
			if (this->platita = false) {
				if (f.suma_platita <= f.pret_initial)
					this->suma_platita = f.suma_platita;
				this->nr_rate = f.nr_rate;
			}
		}
		return *this;
	}

	//ostream
	friend ostream& operator<<(ostream& out, const Furnizor& f) {
		out << endl;
		out << "-----------------Furnizorul------------------------";
		out << "\nNumele firmei furnizoare este : " << f.nume_firma;
		out << "\nPretul initial este : " << f.pret_initial;
		out << "\nPretul final este :" << f.pret_initial + (f.pret_initial * TVA);
		if (f.platita == true)
			out << "\nMasian a fost platita integral";
		else {
			out << "\nMasina nu a fost platita integral";
			out << "\nPana in acest moment s-au achitat " << f.suma_platita << " euro";
			out << "\nFirma mai are de plata " << f.pret_initial - f.suma_platita << "  euro";
			out << "\n Si vor fi platiti in " << f.nr_rate << " rate" << " ( " << (f.pret_initial - f.suma_platita) / f.nr_rate << " euro/ luna )";

		}
		return out;
	}
	//istream
	friend istream& operator >>(istream& in, Furnizor& f) {
		cout << endl;
		cout << "-----------------Furnizorul------------------------";
		cout << "\nNumele firmei furnizoare este : ";

		char aux[232];
		in >> aux;
		delete[] f.nume_firma;
		f.nume_firma = new char[strlen(aux) + 1];
		strcpy(f.nume_firma, aux);

		/*delete[]f.nume_firma;
		char aux[100];
		in.getline(aux, 99);
		f.nume_firma = new char[strlen(aux) + 1];
		strcpy(f.nume_firma, aux);
		in.ignore();*/

		/*delete[]f.nume_firma;
		cout << endl;
		cout << "\n-----------------Furnizor-----------------";
		cout << "\nNumele firmei furnizoare este : ";
		char aux[100];
		in.getline(aux, 99);
		f.nume_firma = new char[strlen(aux) + 1];
		strcpy(f.nume_firma, aux);
		in.ignore();*/

		cout << "\nPretul initial este : "; in >> f.pret_initial;

		cout << "\nSuma achitata pana in acest moment : "; in >> f.suma_platita;
		if (f.suma_platita < f.pret_initial) {
			f.platita = false;
			cout << "\nNumarul de rate dorite : "; in >> f.nr_rate;

		}
		else
			if (f.suma_platita == f.pret_initial)
				cout << "\nMasina a fost achitata";
			else throw new exception("Suma achitata nu poate fi mai mare decat pretul");

		return in;
	}
	//setteri
	void setnume_firma(const char* nume_firma) {
		delete[]this->nume_firma;
		this->nume_firma = new char[strlen(nume_firma) + 1];
		strcpy(this->nume_firma, nume_firma);
	}
	void setpret_initial(float pret_initial) {
		this->pret_initial = pret_initial;
	}
	void setplatita(bool platita, float suma_platita, int nr_rate) {
		this->platita = platita;
		if (platita == false && suma_platita <= this->pret_initial) {
			this->suma_platita = suma_platita;
			this->nr_rate = nr_rate;
		}
		else
		{
			this->suma_platita = 0;
			this->nr_rate = 0;
		}
	}

	//getter
	float getTVA() {
		return TVA;
	}
	int getid() {
		return this->id;
	}
	char* getnume_firma() {
		return this->nume_firma;
	}
	float get_pretinitial() {
		return this->pret_initial;
	}
	float getpret_final() {
		return this->pret_initial * this->TVA + this->pret_initial;
	}
	bool getplatita() {
		return this->platita;
	}
	float getsumaplatita() {
		return this->suma_platita;
	}
	float getnr_rate() {
		return this->nr_rate;
	}
	//operator negatie
	bool operator!() {
		if (this->platita == true)
			return true;
		else return false;
	}
	//operator cast explicit
	explicit operator int() {
		return this->pret_initial;
	}
	//operator ++(Pre-incrementare)
	Furnizor& operator ++() {
		this->nr_rate++;
		return *this;
	}
	//operator ++(Post-incrementare
	Furnizor& operator++(int) {
		Furnizor copie = *this;
		this->nr_rate++;
		return copie;
	}
	//operator +=
	Furnizor operator +=(float suma) {
		this->suma_platita += suma;
		return*this;
	}
	//functie
	float rest_de_plata() {
		float rest;

		rest = this->pret_initial - this->suma_platita;

		return rest;
	}

};
float Furnizor::TVA = 0.19;

enum Tip { SUV = 0, HATCHBACK = 1, CROSSOVER = 2, CONVERTIBLE = 3, SPORT_CAR = 4, COUPE = 5, NECUNOSCUT = 6 };
enum CUTIE { Automata = 0, Manuala = 1, Anonim = 2 };
enum Combustibil { Benzina = 0, Motorina = 1, nestiut = 2 };
class Informatii_masina :public Masina {
private:
	Tip tip;
	int capacitatea_cilindrica;
	int nr_usi;
	float km;
	string data_primei_inmatriculari;
	bool stare;//noua sau veche
	CUTIE cutie;
	Combustibil combustibil;
	int nr_proprietri_anteriori;
	char* culoare;
public:
	//constructor default
	Informatii_masina(Tip tip, CUTIE cutie, Combustibil combustibil) :Masina() {
		this->tip = tip;
		this->cutie = cutie;
		this->combustibil = combustibil;
		this->capacitatea_cilindrica = 0;
		this->km = 0;
		this->nr_usi = 4;
		this->stare = false;
		this->data_primei_inmatriculari = "Necunoscuta";
		this->nr_proprietri_anteriori = 0;
		this->culoare = new char[strlen("Necunoscuta") + 1];
		strcpy(this->culoare, "Necunoscuta");

	}

	//constructor cu toti parametrii
	Informatii_masina(Tip tip, CUTIE cutie, Combustibil combustibil,
		int capacitate_cilindrica, float km, bool stare, int nr_proprietari_anteriori, string data_primei_inmatriculari, const char* culoare, int nr_usi,
		string marca, const char* model, int an_fabricatie, int nr_revizii, float* pret_revizii, float pret) :Masina(marca, model, an_fabricatie, nr_revizii, pret_revizii, pret) {
		this->tip = tip;
		this->cutie = cutie;
		this->combustibil = combustibil;
		this->capacitatea_cilindrica = capacitatea_cilindrica;
		this->nr_usi = nr_usi;
		this->stare = stare;
		if (stare == true)
		{
			this->km = 0;
			this->data_primei_inmatriculari = "Nu a fost inmatriculata";
			this->nr_proprietri_anteriori = 0;

		}
		else
		{
			this->km = km;
			this->data_primei_inmatriculari = data_primei_inmatriculari;
			this->nr_proprietri_anteriori = nr_proprietri_anteriori;
		}

		this->culoare = new char[strlen(culoare) + 1];
		strcpy(this->culoare, culoare);
	}
	// Nu se poate dezaloca copilul
	//Constructor de copiere
	Informatii_masina(const Informatii_masina& i) :Masina(i) {
		this->tip = i.tip;
		this->cutie = i.cutie;
		this->combustibil = i.combustibil;
		this->capacitatea_cilindrica = i.capacitatea_cilindrica;
		this->nr_usi = i.nr_usi;
		this->km = i.km;
		this->stare = i.stare;
		this->data_primei_inmatriculari = i.data_primei_inmatriculari;
		this->nr_proprietri_anteriori = i.nr_proprietri_anteriori;
		this->culoare = new char[strlen(i.culoare) + 1];
		strcpy(this->culoare, i.culoare);
	}

	//operator =
	Informatii_masina& operator =(const Informatii_masina& i) {
		if (this != &i) {
			Masina::operator=(i);//aici se apeleaza operatorul egal din parinte
			this->tip = i.tip;
			this->cutie = i.cutie;
			this->combustibil = i.combustibil;
			this->capacitatea_cilindrica = i.capacitatea_cilindrica;
			this->nr_usi = i.nr_usi;
			this->km = i.km;
			this->stare = i.stare;
			this->data_primei_inmatriculari = i.data_primei_inmatriculari;
			this->nr_proprietri_anteriori = i.nr_proprietri_anteriori;
			this->culoare = new char[strlen(i.culoare) + 1];
			strcpy(this->culoare, i.culoare);
		}
		return *this;
	}
	//ostream
	friend ostream& operator<<(ostream& out, const Informatii_masina& i) {
		out << endl;
		out << (Masina)i;
		out << "\n-----------------Informatii suplimentare masina------------------------";
		out << "\nTip masina :" << i.tip;
		out << "\nCutie : " << i.cutie;
		out << "\nCombustibil : " << i.combustibil;
		out << "\nCapacitatea cilindrica : " << i.capacitatea_cilindrica;
		out << "\nNumarul de usi : " << i.nr_usi;
		out << "\nKm : " << i.km;
		out << "\nStare (Masina noua/ Masina veche) : " << i.stare;
		out << "\nData primei inmatriculari" << i.data_primei_inmatriculari;
		out << "\nNumarul Proprietarilor anteriori : " << i.nr_proprietri_anteriori;
		out << "\nCuloarea este : " << i.culoare;
		out << "\nInformatii: ";
		out << "\nSUV=0,HATCHBACK=1,CROSSOVER=2,CONVERTIBLE=3,SPORT_CAR=4,COUPE=5,NECUNOSCUT=6";
		out << "\nCutie : Automata=0, Manuala=1, Anonim =2";
		out << "\nCombustibil : Benzina=0, Motorina =1, nestiut =2";
		return out;
	}


	//istream
	friend istream& operator>>(istream& in, Informatii_masina& i) {

		cout << "\nMarca: " << i.getMarca();
		cout << "\nAnul :" << i.getAn_fabricatie();
		cout << "\nIntrouce-ti informatii despre masina ";
		//cout << "\nTip masina :"; in >> i.tip;
		//cout << "\nCutie :"; in >> i.cutie;
		cout << "\nData primei inmatriculari "; in >> i.data_primei_inmatriculari;
		in.ignore();
		cout << "\nCuloarea este : ";
		delete[]i.culoare;
		char aux[100];
		in.getline(aux, 99);
		i.culoare = new char[strlen(aux) + 1];
		strcpy(i.culoare, aux);
		cout << "\nCapacitate cilindrica : "; in >> i.capacitatea_cilindrica;
		cout << "\nNumarul de usi : "; in >> i.nr_usi;
		cout << "\nKm : "; in >> i.km;
		if (i.km == 0) {
			i.stare = true;
		}
		cout << "\nNumarul Proprietarilor anteriori : "; in >> i.nr_proprietri_anteriori;



		//in >> (Informatii_masina&)i;
		return in;
	}

};
class Client {
private:
	static int contor;
	const int id;
	char* numeclient;
	int nr_achizitii_anterioare;
	float* pret_achizitii_anterioare;
	float suma_disponibila;
	float reducere;

public:


	//fisier binar

	void writeTOFile(fstream& c) {

		//char*
		c.write((char*)&this->numeclient, sizeof(char*));
		//int
		c.write((char*)&this->nr_achizitii_anterioare, sizeof(int));
		//float*
		for (int i = 0; i < this->nr_achizitii_anterioare; i++)
		{
			c.write((char*)&pret_achizitii_anterioare[i], sizeof(pret_achizitii_anterioare[i]));
		}
		//float
		c.write((char*)&this->suma_disponibila, sizeof(float));
		c.write((char*)&this->reducere, sizeof(float));
	}
	//getter
	int getid() {
		return this->id;
	}
	char* getNumeclient() {
		return this->numeclient;
	}
	int getNr_achizitii_anterioare() {
		return this->nr_achizitii_anterioare;
	}
	float* getPRET_achizitii_anterioare() {
		if (this->nr_achizitii_anterioare > 0)
			return this->pret_achizitii_anterioare;
	}
	float getSuma_diponibila() {
		return this->suma_disponibila;
	}
	float getreducere() {
		if (this->nr_achizitii_anterioare > 0)
			return this->reducere;
	}

	//setteri

	void setNumeclient(const char* numeclient) {
		delete[]this->numeclient;
		this->numeclient = new char[strlen(numeclient) + 1];
		strcpy(this->numeclient, numeclient);
	}
	void setPret_achizitii_anterioare(int nr_achizitii, float* pret) {
		delete[] this->pret_achizitii_anterioare;
		this->nr_achizitii_anterioare = nr_achizitii;
		this->pret_achizitii_anterioare = new float[this->nr_achizitii_anterioare];
		for (int i = 0; i < this->nr_achizitii_anterioare; i++) {
			this->pret_achizitii_anterioare[i] = pret[i];
		}
		if (this->nr_achizitii_anterioare > 0) {
			this->reducere = 0.3 * this->nr_achizitii_anterioare;
		}
	}
	void setSuma_disponibila(float suma) {
		this->suma_disponibila = suma;
	}
	//operator ++(Pre-Incrementare)

	Client& operator++() {
		this->suma_disponibila++;
		return *this;
	}

	//operator++ pre-incrementare
	Client& operator++(int) {
		Client copie = *this;
		this->suma_disponibila++;
		return copie;
	}
	//operator+=
	Client& operator+=(float plata) {
		Client copie = *this;
		this->nr_achizitii_anterioare++;
		this->pret_achizitii_anterioare = new float[this->nr_achizitii_anterioare];
		for (int i = 0; i < copie.nr_achizitii_anterioare; i++) {
			this->pret_achizitii_anterioare[i] = copie.pret_achizitii_anterioare[i];
		}
		this->pret_achizitii_anterioare[this->nr_achizitii_anterioare - 1] = plata;
		return*this;
	}
	//operator de indexare
	float& operator[](int index) {
		if (index >= 0 && index <= this->nr_achizitii_anterioare) {
			return this->pret_achizitii_anterioare[index];
		}
	}

	//constructor default
	Client() :id(++contor) {
		this->numeclient = new char[strlen("Necunoscut") + 1];
		strcpy(this->numeclient, "Necunoscut");
		this->nr_achizitii_anterioare = 0;
		this->pret_achizitii_anterioare = nullptr;
		this->suma_disponibila = 0;
		this->reducere = 0;
	}
	//constructor cu toti parametrii
	Client(const char* numeclient, int nr_achizitii_anterioare, float* pret_achizitii_anterioare, float suma_disponibila) :id(++contor) {
		this->numeclient = new char[strlen(numeclient) + 1];
		strcpy(this->numeclient, numeclient);
		this->nr_achizitii_anterioare = nr_achizitii_anterioare;
		this->pret_achizitii_anterioare = new float[nr_achizitii_anterioare];
		for (int i = 0; i < this->nr_achizitii_anterioare; i++) {
			this->pret_achizitii_anterioare[i] = pret_achizitii_anterioare[i];
		}
		this->suma_disponibila = suma_disponibila;
		if (nr_achizitii_anterioare > 0)
			this->reducere = nr_achizitii_anterioare * 0.03;
		else this->reducere = 0;
	}
	//destructor
	~Client() {
		if (this->numeclient != nullptr) {
			delete[]this->numeclient;
		}
		if (this->pret_achizitii_anterioare != nullptr)
		{
			delete[]this->pret_achizitii_anterioare;
		}
	}
	//constructor de copiere
	Client(const Client& c) :id(c.id) {
		this->numeclient = new char[strlen(c.numeclient) + 1];
		strcpy(this->numeclient, c.numeclient);
		this->nr_achizitii_anterioare = c.nr_achizitii_anterioare;
		this->pret_achizitii_anterioare = new float[c.nr_achizitii_anterioare];
		for (int i = 0; i < c.nr_achizitii_anterioare; i++) {
			this->pret_achizitii_anterioare[i] = c.pret_achizitii_anterioare[i];
		}
		this->suma_disponibila = c.suma_disponibila;
		this->reducere = c.nr_achizitii_anterioare * 0.03;
	}
	//operator=
	Client& operator=(const Client& c) {
		if (this != &c) {
			//destructor
			if (this->numeclient != nullptr) {
				delete[]this->numeclient;
			}
			if (this->pret_achizitii_anterioare != nullptr)
			{
				delete[]this->pret_achizitii_anterioare;
			}
			//constructor de copiere
			this->numeclient = new char[strlen(c.numeclient) + 1];
			strcpy(this->numeclient, c.numeclient);
			this->nr_achizitii_anterioare = c.nr_achizitii_anterioare;
			this->pret_achizitii_anterioare = new float[c.nr_achizitii_anterioare];
			for (int i = 0; i < c.nr_achizitii_anterioare; i++) {
				this->pret_achizitii_anterioare[i] = c.pret_achizitii_anterioare[i];
			}
			this->suma_disponibila = c.suma_disponibila;
			this->reducere = c.nr_achizitii_anterioare * 0.03;
		}
		return *this;
	}
	//ostream
	friend ostream& operator<<(ostream& out, const Client& c) {
		out << endl;
		out << "\n-----------------Client-----------------";
		out << "\nId-ul este : " << c.id;
		out << "\nNumele clientului : " << c.numeclient;
		out << "\nNumar achizitii anterioare : " << c.nr_achizitii_anterioare;
		if (c.nr_achizitii_anterioare > 0) {
			out << "\nPretul achizitiilor anterioare : ";
			for (int i = 0; i < c.nr_achizitii_anterioare; i++)
				cout << "  " << c.pret_achizitii_anterioare[i];
			out << "\nReducerea : " << c.reducere;
		}
		out << "\nSuma disponibila : " << c.suma_disponibila;
		return out;
	}
	//istream
	friend istream& operator>>(istream& in, Client& c) {
		cout << endl;
		cout << "\n-----------------Client-----------------";
		cout << "\nNumele clientului : ";
		delete[]c.numeclient;
		char aux[100];
		in.getline(aux, 99);
		c.numeclient = new char[strlen(aux) + 1];
		strcpy(c.numeclient, aux);
		in.ignore();
		cout << "\nNumar achizitii anterioare : "; in >> c.nr_achizitii_anterioare;
		if (c.nr_achizitii_anterioare > 0) {
			delete[]c.pret_achizitii_anterioare;
			cout << "\nPreturile  : ";
			c.pret_achizitii_anterioare = new float[c.nr_achizitii_anterioare];
			for (int i = 0; i < c.nr_achizitii_anterioare; i++)
				in >> c.pret_achizitii_anterioare[i];
			c.reducere = 0.3 * c.nr_achizitii_anterioare;
		}
		cout << "\nSuma disponibila : "; in >> c.suma_disponibila;
		return in;
	}
	//operator cast
	explicit operator int() {
		return this->suma_disponibila;
	}
	//operator negatie
	bool operator!() {
		if (this->nr_achizitii_anterioare > 0) {
			return true;
		}
	}
	//Metoda medie
	float mediePret() {
		float medie;
		float suma = 0;
		for (int i = 0; i < this->nr_achizitii_anterioare; i++) {
			suma += this->pret_achizitii_anterioare[i];
		}

		medie = suma / this->nr_achizitii_anterioare;
		return medie;
	}
	//adaugara
	float minPret() {
		float min = this->pret_achizitii_anterioare[0];
		for (int i = 0; i < this->nr_achizitii_anterioare; i++) {
			if (min > this->pret_achizitii_anterioare[i]) {
				min = this->pret_achizitii_anterioare[i];
			}
		}
		return min;
	}
};
int Client::contor = 0;

class InterfataMotor {
	//functie virtuala pura
	virtual int durataGarantieLuni() = 0;
	virtual int vitezaMaxima() = 0;
};

class ExceptieCustom : exception {
	string message;
public:
	ExceptieCustom(string message) {
		this->message = message;
	}

	string mesajEroare() {
		return this->message;
	}


	char const* what() const {
		return this->message.c_str();//c_str() transforma un string in sir de caractere
	}
};
class Review {

	const int id_Review;
	string mesaj;

	static int counter;

public:

	//de aici scot

	void writeToFile(fstream& f) {
		//pt int
		f.write((char*)&this->id_Review, sizeof(int));


		// pt string
				//int lg = this->mesaj.size() + 1;
				//f.write((char*)&lg, sizeof(lg));
				//f.write(this->mesaj.c_str(), lg);

		//zurini
		int lg = this->mesaj.length() + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->mesaj.data(), lg * sizeof(char));


	}

	void readFromFile(fstream& f) {
		f.read((char*)&id_Review, sizeof(id_Review));
		int lg = 0;
		f.read((char*)&lg, sizeof(lg));
		char aux[200];
		f.read(aux, lg);
		this->mesaj = aux;
	}






	//pana aici




	//constructor default

	Review() :id_Review(counter++) {
		this->mesaj = "Nu exista informatii";
	}

	//constructor cu parametrii

	Review(const int id_Review, string mesaj) :id_Review(id_Review) {
		this->mesaj = mesaj;
	}

	//constructor de copiere
	Review(const Review& review) :id_Review(review.id_Review) {
		this->mesaj = review.mesaj;
	}

	//operator =
	Review& operator=(const Review& review) {
		if (this != &review) {
			this->mesaj = review.mesaj;
		}

		return *this;
	}
	//ostream
	friend ostream& operator<<(ostream& out, const Review& review) {
		out << "Review with ID ";
		out << review.id_Review << " : " << review.mesaj << endl;

		return out;
	}
	//istream
	friend istream& operator>>(istream& in, Review& review) {
		cout << "Mesaj : ";
		char aux[300];
		in.getline(aux, 300);

		review.mesaj = aux;

		return in;
	}
};

int Review::counter = 1;

class Motor : InterfataMotor {
protected:
	//in functie de poluare
	string normaEuro;
	float capacitateCilindrica;
	char* marca;
	int durata = 24;
	int putere;


	//clasa motor are un vector de review-uri (compunere)
	Review* reviews;
	int nrReviews;
public:

	//constructor default
	Motor() {
		this->normaEuro = "E6";
		this->capacitateCilindrica = 1500;

		this->marca = new char[strlen("BMW") + 1];
		strcpy(this->marca, "BMW");

		this->nrReviews = 0;
		this->reviews = nullptr;
		this->putere = 0;
	}

	//constructor cu toti parametrii
	Motor(string normaEuro, float capacitateCilindrica, const char* marca, Review* reviews, int nrReviews, int durata, int putere) {
		this->normaEuro = normaEuro;
		this->capacitateCilindrica = capacitateCilindrica;

		this->marca = new char[strlen(marca) + 1];
		strcpy(this->marca, marca);

		this->nrReviews = nrReviews;

		this->reviews = new Review[nrReviews];
		for (int i = 0; i < nrReviews; i++) {
			this->reviews[i] = reviews[i];
		}

		this->durata = durata;
		this->putere = putere;
	}

	//constructor de copiere
	Motor(const Motor& m) {
		this->normaEuro = m.normaEuro;

		this->capacitateCilindrica = m.capacitateCilindrica;

		this->marca = new char[strlen(m.marca) + 1];
		strcpy(this->marca, m.marca);

		this->nrReviews = m.nrReviews;

		this->reviews = new Review[m.nrReviews];
		for (int i = 0; i < m.nrReviews; i++) {
			this->reviews[i] = m.reviews[i];
		}

		this->durata = m.durata;
		this->putere = m.putere;
	}

	//operator =

	Motor& operator=(const Motor& m) {
		if (this != &m) {
			//dezalocare memorie pt a evita memory leaks
			delete[] this->reviews;
			delete[] this->marca;

			this->normaEuro = m.normaEuro;

			this->capacitateCilindrica = m.capacitateCilindrica;

			this->marca = new char[strlen(m.marca) + 1];
			strcpy(this->marca, m.marca);

			this->nrReviews = m.nrReviews;

			this->reviews = new Review[m.nrReviews];
			for (int i = 0; i < m.nrReviews; i++) {
				this->reviews[i] = m.reviews[i];
			}
			this->durata = m.durata;
			this->putere = m.putere;
		}

		return *this;
	}

	//destructor

	~Motor() {
		if (this->reviews != nullptr) {
			delete[] this->reviews;
		}

		if (this->marca != nullptr) {
			delete[] this->marca;
		}
	}

	//ostream
	friend ostream& operator<<(ostream& out, const Motor& m) {
		out << "Norma Euro : " << m.normaEuro << " , " << " Capacitate Cilindrica : " << m.capacitateCilindrica << " , " << " Marca : " << m.marca << endl;
		for (int i = 0; i < m.nrReviews; i++) {
			out << m.reviews[i];
		}
		return out;
	}
	//istream

	friend istream& operator>>(istream& in, Motor& m) {
		cout << "Motoare\n";

		cout << "Norma Euro : ";
		char aux[300];
		in >> aux;
		m.normaEuro = aux;

		cout << "Capacitate cilindrica : ";
		in >> m.capacitateCilindrica;

		in.ignore();

		cout << "Marca : ";
		in >> aux;

		delete[] m.marca;
		m.marca = new char[strlen(aux) + 1];
		strcpy(m.marca, aux);


		cout << "Nr reviews : ";
		in >> m.nrReviews;

		in.ignore();

		cout << "Reviews : ";
		delete[] m.reviews;
		m.reviews = new Review[m.nrReviews];
		for (int i = 0; i < m.nrReviews; i++) {
			in >> m.reviews[i];
		}

		return in;
	}

	void setNormaEuro(string normaEuro) {
		if (normaEuro.size() <= 1) {
			throw new exception("Norma Euro trebuie sa aiba minim 2 caractere");
		}
		else if (strcmp(normaEuro.c_str(), "E") == 0) {
			throw exception("Norma nu poate fi valoarea E");
		}
		else if (strcmp(normaEuro.c_str(), "Euro") == 0) {
			throw - 100;
		}
		else if (normaEuro.length() > 3) {
			throw new ExceptieCustom("Norma nu poate sa aiba mai mult de 3 caractere");
		}
	}

	void adaugReviewInVector(const Review& review) {
		Review* paux = new Review[nrReviews + 1];

		for (int i = 0; i < nrReviews; i++) {
			paux[i] = reviews[i];
		}

		paux[nrReviews] = review;
		nrReviews++;

		//pt memory leaks
		delete[] reviews;

		reviews = paux;
	}

	//operator +=

	void operator+=(const Review& review) {
		Review* paux = new Review[nrReviews + 1];

		for (int i = 0; i < nrReviews; i++) {
			paux[i] = reviews[i];
		}

		paux[nrReviews] = review;
		nrReviews++;

		delete[] reviews;//evita memory leaks

		reviews = paux;
	}

	void stergeUltimulElementDinVector() {
		Review* paux = new Review[nrReviews - 1];

		for (int i = 0; i < nrReviews - 1; i++) {
			paux[i] = reviews[i];
		}

		nrReviews--;

		delete[] reviews;//evita memory leaks

		reviews = paux;
	}

	// doua metode virtuale
	virtual int durataDeViata() {
		return 10;
	}
	virtual float calculCaiPutere() {
		return this->putere * 1.36;
	}
	int durataGarantieLuni() {
		return durata;
	}

	virtual int vitezaMaxima() {
		return 280;
	}



};


//is a

class motorTermic :public Motor {
	string tip;// ardere externa cu piston,motor wankel(sistem cu piston rotativ,nu are si sitem biela-maniivela)
public:
	//constructor default

	motorTermic() :Motor() {
		this->tip = "Necunoscut";
	}

	//Motor(string normaEuro, float capacitateCilindrica, const char* marca, Review* reviews, int nrReviews)
//constructor cu parametrii

	motorTermic(string tip) :Motor("E6", 1500, "BMW", nullptr, 0, 24, 100) {
		this->tip = tip;
	}

	//constructor

	motorTermic(string tip, string normaEuro, float capacitateCilindrica, const char* marca, Review* reviews, int nrReviews, int durata, int putere) :
		Motor(normaEuro, capacitateCilindrica, marca, reviews, nrReviews, durata, putere) {
		this->tip = tip;
	}

	//constructor de copiere
	motorTermic(const motorTermic& mt) : Motor(mt) {
		this->tip = mt.tip;
	}

	// nu e nevoie de destructor

	//operator egal

	motorTermic& operator=(const motorTermic& mt) {
		if (this != &mt) {
			Motor::operator=(mt);//aici apelezi op= din parinte

			this->tip = mt.tip;
		}

		return *this;
	}
	//ostream
	friend ostream& operator<<(ostream& out, const motorTermic& mt) {
		out << "\n-----------Motor Termic:-------------- " << "\n Tip(ardere externa cu piston, motor Wankel) : " << mt.tip << endl;
		out << (Motor)mt; //transformi copilul in parinte si automat << stie ca tu incerci sa afis. un parinte

		return out;
	}

	friend istream& operator>>(istream& in, motorTermic& mt) {
		cout << "Citire motor termic\n";

		char aux[300];
		cout << "Tip (ardere externa cu piston,motor wankel) : ";
		in.getline(aux, 300);

		mt.tip = aux;


		in >> (Motor&)mt; //folosesc  >> din parinte

		return in;
	}
	int durataDeViata() {
		return 5;
	}

	int durataGarantieLuni() {
		return 60;
	}

	int vitezaMaxima() {
		return 280;
	}

};


class DataAnalyzer {

private:
	struct UserActivity {
		std::string username;
		int time_spent;
		std::time_t login_time;
	};

	std::vector<UserActivity> user_activity_log;
	std::chrono::time_point<std::chrono::system_clock> start;

public:
	void monitor_user_activity(std::string username) {
		start = std::chrono::system_clock::now();
	}

	void stop_monitor_user_activity(std::string username) {
		std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		int time_spent = elapsed_seconds.count();
		UserActivity user_activity;
		user_activity.username = username;
		user_activity.time_spent = time_spent;
		user_activity_log.push_back(user_activity);
	}
	void generate_activity_report() {
		for (auto user : user_activity_log) {
			cout << "User: " << user.username << endl;
			cout << "Time spent: " << user.time_spent << " seconds" << endl;
		}
	}
};

int main() {

	DataAnalyzer analyzer;
	// monitor user activity
	analyzer.monitor_user_activity("Melisa");
	fstream myfile;

	Showroom s1(1400, "Strada Mangaliei nr. 100", 150, 98);
	cout << s1;
	Showroom s2(1401);
	cin >> s2;
	cout << s2;
	Showroom s3(1402);
	s3 = s2;
	cout << s3;
	//apel operator ++ post-incrementare
	s1 = ++s2;
	cout << "\nApel operator ++ post-incrementare" << "  " << s1.getmasini_disponibile();
	//apel operator ++ pre-incrementare
	s1 = s2++;
	cout << "\nApel operator ++ pre-incrementare" << "  " << s1.getmasini_disponibile();

	cout << endl;
	//operator cast explicit
	cout << "\nOperator cast :";
	float capacitate = (float)s1;
	cout << "\nCapacitatea este de : " << capacitate;
	cout << endl;

	//operator negatie
	cout << "\nOperator negatie:   ";
	if (!s1) { cout << "\nCapacitatea este mai mare ca 0"; }
	else cout << "\nCapacitatea este 0";
	cout << endl;

	//operator de comparatie
	cout << "\nOperator de comparatie :";
	if (s1 == s1) {
		cout << "\nRelatia intre ele este de egalitate";
	}
	cout << endl;

	//operator +=
	s1 += 3;
	cout << "\nCapacitatea a crescut la : " << s1.getcapacitate();
	cout << endl;

	cout << "\nFunctii: \n";
	//Locurile diponibile
	s1.Loc_diponibil();
	cout << endl;

	//Apel setter
	cout << "\n-------------Apel setteri-------------";
	s1.setadresa("Strada Muncii, nr.20");
	s1.setcapacite(200);
	s1.setmasini_disponibile(100);
	cout << endl;

	//Apel getteri
	cout << "\n-------------Apel getteri-------------";
	cout << "\nId-ul firmei este : " << s1.getid();
	cout << "\nDenumirea este : " << s1.getdenumirea();
	cout << "\nAdresa este : " << s1.getadresa();
	cout << "\nNumarul masinilor disponibile este de : " << s1.getmasini_disponibile();
	cout << "\nCapacitatea showroom-ului : " << s1.getcapacitate() << "  de masini";
	cout << endl;

	//fisier text
	cout << "\n------------Apel fisier text----------------";
	cout << "\nS-a adaugat o noua inregistrare in fisier\n";

	//scriere in fisier txt
	ofstream sto("Showroom.txt", ios::out);
	if (sto.is_open()) {
		sto << s1;
		sto << s2;
	}

	cout << "\n---------Citire din fisier txt----------------";


	//citire fisier txt
	string line;
	ifstream sti("Showroom.txt", ios::in);
	if (sti.is_open()) {
		while (getline(sti, line)) {
			cout << line << endl;
		}
		sti.close();
	}

	/*myfile.open("Showroom.txt", ios::app);
	if (myfile.is_open()) {
		myfile << s1;
		myfile.close();
	}
	cout << "\nCitire din fisier\n";
	myfile.open("Showroom.txt", ios::in);
	if (myfile.is_open()) {
		string line;
		while (getline(myfile, line)) {
			cout << line << endl;
		}
	}*/


	//fisier separat prin virgula

	cout << "\n---------Scriere in fisier txt(,)----------------\n";

	//citire fisier separat prin ,
	fstream file("Showroom','.txt");
	while (getline(file, line)) {
		istringstream iss(line);
		string adr;
		string capacitate;
		string  nr_masini_disponibile;

		getline(iss, adr, ',');
		getline(iss, capacitate, ',');
		getline(iss, nr_masini_disponibile, ',');

		cout << adr << "  " << capacitate << "  " << nr_masini_disponibile;
		char* adresa = new char[adr.length() + 1];
		strcpy(adresa, adr.c_str());
		int cap = std::stoi(capacitate);
		int nr = std::stoi(nr_masini_disponibile);
		s1.setadresa(adresa);
		s1.setcapacite(cap);
		s1.setmasini_disponibile(nr);

		//citire fisier (,)
		cout << endl << "\n----------Citire fisier csv--------------";
		cout << "\nAdresa este : " << s1.getadresa();
		cout << "\nNumarul masinilor disponibile este de : " << s1.getmasini_disponibile();
		cout << "\nCapacitatea showroom-ului : " << s1.getcapacitate() << "  de masini";
	}


	//Scriere in fisier binar
	/*fstream fOUT("Showroombin.txt", ios::out | ios::binary);
	s1.writeTOFile(fOUT);
	fOUT.close();*/

	//fisier binar
	// 
		//citire
	cout << endl;
	cout << "\n-----------------Scriere fisier binar-----------------------\n";
	fstream sbo("Showroomb.bin", ios::out | ios::binary);
	if (sbo.is_open()) {
		s1.writeTOFile(sbo);
		s2.writeTOFile(sbo);
		s3.writeTOFile(sbo);
		sbo.close();
	}
	//fstream fin("fisier.txt", ios::in | ios::binary);

	//scriere fisier binar
	cout << "\n-----------------Citire fisier binar-----------------------\n";
	fstream sbi("Showroomb.bin", ios::in | ios::binary);
	if (sbi.is_open()) {
		s1.readFromFile(sbi);
		cout << s1;
		cout << s2;
		cout << s3;
		sbi.close();
	}

	//raport

	cout << "\n----------Raport-------------------";
	ofstream File10("RaportShowroom.csv");
	File10 << "id,adresa,capacitate, numarul de masini dsonibile" << endl;
	File10 << s1.getid() << "," << s1.getadresa() << "," << s1.getcapacitate() << "," << s1.getmasini_disponibile() << endl;
	File10 << s2.getid() << "," << s2.getadresa() << "," << s2.getcapacitate() << "," << s2.getmasini_disponibile() << endl;
	File10 << s3.getid() << "," << s3.getadresa() << "," << s3.getcapacitate() << "," << s3.getmasini_disponibile() << endl;
	File10.close();

	//meniu
	int choice;
	do {
		cout << "\n1.Id-ul";
		cout << "\n2.Adresa";
		cout << "\n3.Capacitatea";
		cout << "\n4.Masini disponibile";
		cout << "\n5.Iesire";
		cout << "\nCe alegeti:";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << s1.getid();
			cout << endl;
			break;
		case 2:
			cout << s1.getadresa();
			cout << endl;
			break;
		case 3:
			cout << s1.getcapacitate();
			cout << endl;
			break;
		case 4:
			cout << s1.getmasini_disponibile();
			cout << endl;
			break;
		case 5:
			cout << "\nIesire";
			break;

		}
	} while (choice != 5);


	//clasa Masina
	Masina m1("Mini", "Cooper S", 2016, 2, new float[2]{ 120,150 }, 13500.50);
	cout << m1;
	Masina m3("Mini", "Cooper S", 2016, 2, new float[2]{ 120,150 }, 13500.50);
	cout << m3;
	Masina m2;
	cin >> m2;
	cout << m2;

	//operator index
	cout << endl;
	cout << "\nOperator index : ";
	cout << m1[0];

	//operator +=
	cout << endl;
	cout << "\nOperator += ";
	m1 += 100;

	cout << "\nPreturile reviziilor sunt : ";
	for (int i = 0; i < m1.getNr_revizii(); i++)
	{
		cout << m1.getPret_revizii()[i] << "  ";
	}

	//apel operator ++ post-incrementare
	cout << endl;
	m1 = ++m1;
	cout << "\nApel operator ++ post-incrementare" << "  " << m1.getPret();

	//apel constructor de copiere
	cout << endl;
	cout << "\nConstructor de copiere ";
	m2 = m1;
	cout << m2;


	//apel operator ++ pre-incrementare
	cout << endl;
	m1 = m2++;
	cout << "\nApel operator ++ pre-incrementare" << "  " << m1.getPret();

	//operator cast
	cout << endl;
	cout << "\nOpertor cast : " << (int)m1;

	//Apel setter
	cout << endl;
	cout << "\n-------------Apel setteri-------------";
	m3.setModel("A Class");
	m3.setMarca("Mercedes Benz");
	m3.setAn_fabricatie(2020);
	m3.setPret(17000);
	m3.setPret_revizii(3, new float[3]{ 150,200,500 });


	//Apel getteri
	cout << endl;
	cout << "\n-------------Apel getteri-------------";
	cout << "\nId-ul este : " << m3.getid();
	cout << "\nMarca : " << m3.getMarca();
	cout << "\nModel : " << m3.getModel();
	cout << "\nAn fabricatie :" << m3.getAn_fabricatie();
	cout << "\nNumarul reviziilor : " << m3.getNr_revizii();
	cout << "\nPretul reviziilor : ";
	for (int i = 0; i < m3.getNr_revizii(); i++)
	{
		cout << m3.getPret_revizii()[i] << "  ";
	}
	cout << "\nPret: " << m3.getPret() << " euro";
	cout << endl;

	//fisier text
	cout << "\n------------Apel fisier text----------------";
	cout << "\nS-a adaugat o noua inregistrare in fisier\n";
	ofstream mto("Masina.txt", ios::out);
	if (mto.is_open()) {
		mto << m3;
		mto << m2;
		mto.close();
	}

	cout << "\n------------Citire fisier text----------------";
	//string line;
	ifstream mti("Masina.txt", ios::in);
	if (mti.is_open()) {
		while (getline(mti, line)) {
			cout << line << endl;
		}
		mti.close();
	}

	//fisier csv

   /*string marca;
	   char* model;
	   int an_fabricatie;
	   int nr_revizii;
	   float* pret_revizii;
	   float pret;*/

	fstream file2("Masina','.txt");


	// Read each line of the file
	while (getline(file2, line))
	{
		// Create an input string stream from the line
		istringstream iss(line);

		// Extract the values from the line
		string value1;
		string value2;
		string value3;
		string value4;
		string value5;
		string value6;
		getline(iss, value1, ',');  // <-- Read value1 and stop at comma
		getline(iss, value2, ',');  // <-- Read value2 and stop at comma
		getline(iss, value3, ',');  // <-- Read value3 and stop at comma
		getline(iss, value4, ',');
		getline(iss, value5, ',');
		getline(iss, value6, ',');
		// Print the values
		cout << endl;
		cout << "\n-------Citire fisier csv---------";
		cout << "\nMarca: " << value1 << endl;
		cout << "Model: " << value2 << endl;
		cout << "An fabricatie: " << value3 << endl;
		cout << "Numar revizii: " << value4 << endl;
		cout << "Pret revizi: " << value5 << endl;
		cout << "Pret: " << value6 << endl;
	}

	// Close the file
	file2.close();

	//fisier binar
   /*cout << "\n------Scriere in fisier binar-----------";
   fstream fout("Masinabin.txt", ios::out | ios::binary);
   m1.writeToFile(fout);
   fout.close();
   */

   //fisier binar

	cout << "\n------------Apel fisier binar----------------";
	fstream mbo("Masina.bin", ios::out | ios::binary);
	if (mbo.is_open()) {
		m1.writeToFile(mbo);
		m2.writeToFile(mbo);
		m3.writeToFile(mbo);
		mbo.close();
	}

	cout << "\n------------Afisare continut fisier binar----------------";
	fstream mbi("Masina.bin", ios::in | ios::binary);
	if (mbi.is_open()) {
		cout << ".";
		m1.readFromFile(mbi);
		m2.readFromFile(mbi);
		m3.readFromFile(mbi);
		//cout << m1;
		cout << m2;
		cout << m3;
		mbi.close();
	}

	//raport
	cout << "\n----------Raport-------------------";
	ofstream File12("RaportMasini.csv");
	File12 << "Marca,Model,An fabricatie,Pret, Numarul de revizii, Pretul reviziilor anterioare" << endl;
	File12 << m1.getMarca() << "," << m1.getModel() << "," << m1.getAn_fabricatie() << "," << m1.getPret() << "," << m1.getNr_revizii() << ",";
	for (int i = 0; i < m1.getNr_revizii(); i++)
		File12 << m1.getPret_revizii()[i] << " ";
	File12 << endl;
	File12 << m2.getMarca() << "," << m2.getModel() << "," << m2.getAn_fabricatie() << "," << m2.getPret() << "," << m2.getNr_revizii() << ",";
	for (int i = 0; i < m2.getNr_revizii(); i++)
		File12 << m2.getPret_revizii()[i] << " ";
	File12 << endl;
	File12 << m3.getMarca() << "," << m3.getModel() << "," << m3.getAn_fabricatie() << "," << m3.getPret() << "," << m3.getNr_revizii() << ",";
	for (int i = 0; i < m3.getNr_revizii(); i++)
		File12 << m3.getPret_revizii()[i] << " ";
	File12 << endl;
	File12.close();

	//meniu

	do {
		cout << "\n-----------------Meniu-------------------\n";
		cout << "\n1.Marca";
		cout << "\n2.Model";
		cout << "\n3.Anul fabricatiei";
		cout << "\n4.Pretul reviziilor";
		cout << "\n5.Pret masina";
		cout << "\n6.Iesire";
		cout << "\nCe alegeti:";
		cin >> choice;
		cout << "\n-----Rezultat---------\n";

		switch (choice) {
		case 1:
			cout << m2.getMarca();
			cout << endl;
			break;
		case 2:
			cout << m2.getModel();
			cout << endl;
			break;
		case 3:
			cout << m2.getAn_fabricatie();
			cout << endl;
			break;
		case 4:
			for (int i = 0; i < m2.getNr_revizii(); i++)
				cout << m2.getPret_revizii()[i] << " ";
			cout << endl;
			break;
		case 5:
			cout << m2.getPret();
			break;
		case 6:
			cout << "\nIesire";
			break;

		}
	} while (choice != 6);


	//Furnizor
	Furnizor f1(1500, "BMW", 15000, false, 10000, 2);
	cout << f1;
	Furnizor f2(1400);
	cout << f1;
	Furnizor f3(1401, "BMW", 15000, false, 1400, 4);
	cout << f3;
	Furnizor f4(1500);
	cin >> f4;
	cout << f4;
	//setter
	f1.setnume_firma("Skoda");
	f1.setpret_initial(1700.60);
	f1.setplatita(true, 0, 0);
	//functia
	cout << "\nRest de plata: ";
	cout << f1.rest_de_plata();
	//Operator ++(Pre-incrementare)
	f4 = ++f4;
	cout << "\nApel operator++(pre)" << f4.getnr_rate();
	//Operator ++(Post-incrementare)
	f4 = f1++;
	cout << "\n Apel operator ++(post) " << f4.getnr_rate();
	//operator cast explicit
	cout << "\nOperator cast explicit: " << (int)f3;
	//opeartor +=suma
	f4 += 100;
	cout << "\nPana in acest moment s-au achitat : " << f4.getsumaplatita() << "  euro";
	//getteri
	cout << "\n-------------Apel getter-------------";
	cout << "\nTVA : " << f1.getTVA();
	cout << "\nId-ul :" << f1.getid();
	cout << "\nNumele furnizorului : " << f1.getnume_firma();
	cout << "\nPretul initial : " << f1.get_pretinitial();
	cout << "\nPret final : " << f1.getpret_final();
	cout << "\nMasina a fost platita : " << f1.getplatita();
	cout << "\nSuma achitata pana in acest moment : " << f1.getsumaplatita();
	cout << "\nNumarul ratelor : " << f1.getnr_rate();

	//fisier text
	cout << "\n------------Apel fisier text----------------\n";
	cout << "\nS-a adaugat o noua inregistrare in fisier\n";
	ofstream fto("Furnizor.txt", ios::out);
	if (fto.is_open()) {
		fto << f1;
		fto << f3;
		fto.close();
	}

	cout << "\n----------Citire din fisier---------------\n";
	ifstream fti("Furnizor.txt", ios::in);
	if (fti.is_open()) {
		string line;
		while (getline(fti, line)) {
			cout << line << endl;
		}
		fti.close();
	}



	//meniu
	do {
		cout << "\n-----------------Meniu-------------------\n";
		cout << "\n1.Id-ul";
		cout << "\n2.Numele furnizorului";
		cout << "\n3.Pret initial";
		cout << "\n4.Starea masinii(platita/neplatita)";
		cout << "\n5.Numarul de rate";
		cout << "\n6.Pret final";
		cout << "\n7.Suma platita pana in acest moment";
		cout << "\n8.Iesire";
		cout << "\nCe alegeti:";
		cin >> choice;
		cout << "\n-----Rezultat---------\n";

		switch (choice) {
		case 1:
			cout << f1.getid();
			cout << endl;
			break;
		case 2:
			cout << f1.getnume_firma();
			cout << endl;
			break;
		case 3:
			cout << f1.get_pretinitial();
			cout << endl;
			break;
		case 4:
			cout << f1.getplatita();
			cout << endl;
			break;
		case 5:
			cout << f1.getnr_rate();
			break;

		case 6:
			cout << f1.getpret_final();
			break;
		case 7:
			cout << f1.getsumaplatita();
			break;
		case 8:
			cout << "\nIesire";
			break;

		}
	} while (choice != 8);

	/*char* nume_firma;
		float pret_initial;
		float pret_final;
		bool platita;
		float suma_platita;
		int nr_rate;*/

	fstream file3("Furnizor','.txt");


	// Read each line of the file
	while (getline(file3, line))
	{
		// Create an input string stream from the line
		istringstream iss(line);

		// Extract the values from the line
		string value1;
		string value2;
		string value3;
		string value4;
		string value5;
		getline(iss, value1, ',');  // <-- Read value1 and stop at comma
		getline(iss, value2, ',');  // <-- Read value2 and stop at comma
		getline(iss, value3, ',');  // <-- Read value3 and stop at comma
		getline(iss, value4, ',');
		getline(iss, value5, ',');

		// Print the values
		cout << endl;
		cout << "\n-------Citire fisier csv---------";
		cout << "\nNume firma : " << value1 << endl;
		cout << "Pret initial: " << value2 << endl;
		cout << "Starea masinii (platita/neplatita) : " << value3 << endl;
		cout << "Suma platita: " << value4 << endl;
		cout << "Numarul de rate : " << value5 << endl;

	}

	// Close the file
	file3.close();

	//fisier binar

	cout << "\n------Scriere in fisier binar-----------";
	fstream fOut("Furnizorbin.txt", ios::out | ios::binary);
	f1.writeTOFile(fOut);
	fOut.close();



	Informatii_masina i1(SUV, Automata, Benzina, 1500, 1500, false, 2, "14-10-2002", "rosie", 4, "Mini", "Cooper", 2000, 2, new float[2]{ 150,300 }, 1500);
	cout << i1;

	Informatii_masina i2(HATCHBACK, Manuala, Motorina, 1500, 1500, false, 2, "14-10-2019", "neagra", 5, "volkswagen", "Tiguan", 2018, 1, new float[6]{ 150 }, 25000);
	cout << i2;
	//constructor de copiere
	Informatii_masina i3(i1);
	cout << i3;
	//operator =
	i3 = i2;
	cout << i3;
	cin >> i3;
	cout << i3;

	//fisier text
	cout << "\n------------Apel fisier text----------------\n";
	cout << "\nS-a adaugat o noua inregistrare in fisier\n";
	myfile.open("Informatii_suplimentare.txt", ios::app);
	if (myfile.is_open()) {
		myfile << i1;
		myfile.close();
	}
	cout << "\nCitire din fisier\n";
	myfile.open("Informatii_suplimentare.txt", ios::in);
	if (myfile.is_open()) {
		string line;
		while (getline(myfile, line)) {
			cout << line << endl;
		}
	}

	Client c1;
	Client c2("Maria Popescu", 2, new float[2]{ 15000,30000 }, 25000);
	cout << c2;
	Client c3;
	//cin >> c3;
	cout << c3;

	//Setteri
	c1.setNumeclient("AZZA DENIZ");
	c1.setPret_achizitii_anterioare(2, new float[2]{ 15000,30000 });
	c1.setSuma_disponibila(60000.56);
	cout << "\n------------A fost apelat Setter-ul------------";
	cout << "\n------------Apel Getter------------";
	cout << "\nNumele clientului este : " << c1.getNumeclient();
	cout << "\nNumarul achizitiilor anterioare : " << c1.getNr_achizitii_anterioare();
	cout << "\nPreturile achizitiilor anterioare : ";
	for (int i = 0; i < c1.getNr_achizitii_anterioare(); i++)
	{
		cout << "  " << c1.getPRET_achizitii_anterioare()[i];
	}
	cout << "\nReducerea pe care o va primi clientul  : " << c1.getreducere();
	cout << "\nSuma detiuta de client : " << c1.getSuma_diponibila();

	c1 += 25000;
	cout << "\nPreturile achizitiilor anterioare : ";
	for (int i = 0; i < c1.getNr_achizitii_anterioare(); i++)
	{
		cout << "  " << c1.getPRET_achizitii_anterioare()[i];

	}
	cout << "\n--Operator index";
	cout << "\nPretul de pe pozitia 1 este : ";
	cout << c1[0];

	cout << "\n---Operator cast";
	cout << "\nSuma disponibila este : ";
	cout << (int)c1;

	cout << "\nMedia achizitiilor anterioare";
	cout << "  " << c1.mediePret();

	cout << "\nPretul minim este : ";
	cout << c1.minPret();

	c1.setPret_achizitii_anterioare(0, new float[0]{});
	if (!c1)
		cout << "\nExista achizitii anterioare.";
	else cout << "\nNu exista achizitii anterioare.";

	//fisier text
	cout << "\n------------Apel fisier text----------------\n";
	cout << "\nS-a adaugat o noua inregistrare in fisier\n";
	myfile.open("Client.txt", ios::out);
	if (myfile.is_open()) {
		myfile << c1;
		myfile << c2;
		myfile.close();
	}
	cout << "\nCitire din fisier\n";
	myfile.open("Client.txt", ios::in);
	if (myfile.is_open()) {
		string line;
		while (getline(myfile, line)) {
			cout << line << endl;
		}
	}

	do {
		cout << "\n-----------------Meniu-------------------\n";
		cout << "\n1.Nume client";
		cout << "\n2.Numarul achizitiilor anterioare";
		cout << "\n3.Preturile achizitiilor anterioare";
		cout << "\n4.Reducere";
		cout << "\n5.Bugetul clientului";
		cout << "\n6.Iesire";
		cout << "\nCe alegeti:";
		cin >> choice;
		cout << "\n-----Rezultat---------\n";

		switch (choice) {
		case 1:
			cout << c2.getNumeclient();
			cout << endl;
			break;
		case 2:
			cout << c2.getNr_achizitii_anterioare();
			cout << endl;
			break;
		case 3:
			for (int i = 0; i < c2.getNr_achizitii_anterioare(); i++)
			{
				cout << "  " << c2.getPRET_achizitii_anterioare()[i];

			}
			cout << endl;
			break;
		case 4:
			cout << c2.getreducere();
			cout << endl;
			break;
		case 5:
			cout << c2.getSuma_diponibila();
			break;
		case 6:
			cout << "\nIesire";
			break;

		}
	} while (choice != 6);

	/*char* numeclient;
		int nr_achizitii_anterioare;
		float* pret_achizitii_anterioare;
		float suma_disponibila;
		float reducere;*/
	fstream file4("Client','.txt");


	// Read each line of the file
	while (getline(file4, line))
	{
		// Create an input string stream from the line
		istringstream iss(line);

		// Extract the values from the line
		string value1;
		string value2;
		string value3;
		string value4;
		string value5;
		getline(iss, value1, ',');  // <-- Read value1 and stop at comma
		getline(iss, value2, ',');  // <-- Read value2 and stop at comma
		getline(iss, value3, ',');  // <-- Read value3 and stop at comma
		getline(iss, value4, ',');
		getline(iss, value5, ',');

		// Print the values
		cout << endl;
		cout << "\n-------Citire fisier csv---------";
		cout << "\nNume client : " << value1 << endl;
		cout << "Numarul achzitiilor anterioare : " << value2 << endl;
		cout << "Pretul achizitiilor anterioare: " << value3 << endl;
		cout << "Suma disponibila : " << value4 << endl;
		cout << "Reducere: " << value5 << endl;

	}

	// Close the file
	file4.close();

	//fisier binar
	fstream fOUt("Clientbin.txt", ios::out | ios::binary);
	c1.writeTOFile(fOUt);
	fOUt.close();

	cout << "\n----------Raport-------------------";
	ofstream File13("RaportClienti.csv");
	File13 << "Nume,id,Suma disponibila,Numarul achizitiilor ant., Reducere, Pretul achizitiilor antrioare" << endl;
	File13 << c1.getNumeclient() << "," << c1.getid() << "," << c1.getSuma_diponibila() << "," << c1.getPRET_achizitii_anterioare() << "," << c1.getreducere() << ",";
	for (int i = 0; i < c1.getNr_achizitii_anterioare(); i++)
		File13 << c1.getPRET_achizitii_anterioare()[i];
	File13 << endl;

	File13 << "Nume,id,Suma disponibila,Numarul achizitiilor ant., Reducere, Pretul achizitiilor antrioare" << endl;
	File13 << c2.getNumeclient() << "," << c2.getid() << "," << c2.getSuma_diponibila() << "," << c2.getPRET_achizitii_anterioare() << "," << c2.getreducere() << ",";
	for (int i = 0; i < c2.getNr_achizitii_anterioare(); i++)
		File13 << c2.getPRET_achizitii_anterioare()[i];
	File13 << endl;

	File13 << "Nume,id,Suma disponibila,Numarul achizitiilor ant., Reducere, Pretul achizitiilor antrioare" << endl;
	File13 << c3.getNumeclient() << "," << c3.getid() << "," << c3.getSuma_diponibila() << "," << c3.getPRET_achizitii_anterioare() << "," << c3.getreducere() << ",";
	for (int i = 0; i < c3.getNr_achizitii_anterioare(); i++)
		File13 << c3.getPRET_achizitii_anterioare()[i];
	File13 << endl;



	Review r1, r2;

	Review r6(1400, "S-a stricat intr-un an");
	Review r7(1401, "Nu am avut probleme");
	Review r8(1402, "Consum mare");
	Review r5(1403, "Multumita");
	Review r3(1402, "Momentan nu s-a strucat");
	Review r4(1402, "Nu permite oprirea functiei start-stop");

	//vector review
	Review reviews1[3] = { r1,r3,r8 };
	Review reviews2[4] = { r2,r4,r6,r7 };
	Review reviews3[2] = { r3,r8 };

	//Motor
	Motor mo1("E6", 2000, "BMW", reviews1, 3, 36, 110);
	Motor mo2("E5", 1500, "Mercedes", reviews2, 4, 60, 120);

	cout << mo1 << endl;
	cout << mo2 << endl;

	//motorTermic

	motorTermic mt1;
	cout << mt1;

	motorTermic mt2("Ardere externa cu piston", "E6", 1500, "BMW", reviews1, 3, 48, 100);
	cout << mt2;

	//try catch
		/*try {
			mt2.setNormaEuro("C");

			mt2.setNormaEuro("CC");
		}
		catch (int x) {
			cout << x << endl;
		}
		catch (exception* e) {
			cout << e->what() << endl;
		}


		try {
			mt2.setNormaEuro("BB");
		}
		catch (exception e) {
			cout << e.what() << endl;
		}*/

	try {
		mt2.setNormaEuro("BB bbb bbb bbb bbb");
	}
	catch (ExceptieCustom* e) {
		cout << e->mesajEroare() << endl;
	}

	cout << "early-binding : \n\n";
	//early-binding:
	Motor mo3;
	Motor mo4 = mt2; //(upcasting -> transformi un copil in parinte)

	cout << "Durata de viata : " << mo3.durataDeViata() << endl;
	cout << "Durata de viata : " << mo4.durataDeViata() << endl << endl;


	cout << "late-binding : \n\n";
	//late-binding - folosim pointeri pt a demonstra acest concept
	Motor* pointerEl1 = new motorTermic("Ardere externa cu piston", "E6", 1500, "BMW", reviews1, 3, 48, 100);
	Motor* pointerEl2 = new motorTermic("Ardere externa cu piston", "E5", 1400, "BMW", reviews1, 3, 12, 110);
	Motor* pointerEl3 = new motorTermic("Ardere externa cu piston", "E5", 2000, "BMW", reviews1, 3, 36, 130);
	Motor* pointerEl4 = new Motor();


	cout << "Durata de viata : " << pointerEl1->durataDeViata() << endl;

	cout << "Durata de viata : " << pointerEl4->durataDeViata() << endl << endl;


	cout << "polimorfism : \n\n";
	Motor** vectorDePointeri = new Motor * [4];
	vectorDePointeri[0] = pointerEl1;
	vectorDePointeri[1] = pointerEl2;
	vectorDePointeri[2] = pointerEl3;
	vectorDePointeri[3] = pointerEl4;


	for (int i = 0; i < 4; i++) {
		cout << "durataDeViata : " << vectorDePointeri[i]->durataDeViata() << endl;
		cout << "durataGarantieLuni : " << vectorDePointeri[i]->durataGarantieLuni() << endl;
		cout << "cai putere : " << vectorDePointeri[i]->calculCaiPutere() << endl;
	}


	//lucru cu stl

	cout << "\n------STL VECTOR--------\n";
	vector<Review> reviews;
	reviews.push_back(Review(1, "Motor bun!"));
	reviews.push_back(Review(2, "Multumita!"));
	reviews.push_back(Review(3, "Consum mic!"));
	reviews.push_back(Review(4, "Intretinere costisitoare!"));
	reviews.push_back(Review(5, "Piston stricat!"));


	/*vInt.push_back(r1);
	vInt.push_back(20);
	vInt.push_back(30);*/
	for (int i = 0; i < reviews.size(); i++)
		cout << reviews[i] << " ";
	vector<Review>::iterator it;
	cout << endl;
	for (it = reviews.begin(); it != reviews.end(); it++)
		cout << *it << " ";


	cout << "\n------STL LIST--------\n";
	/*	vector<Motor>lMotor;
		//motors.push_back(Motor("E6", 2000, "BMW", reviews1, 3, 36));
		//motors.push_back(Motor("E5", 1500, "Mercedes", reviews2, 4, 26));


		for (itlist = lMotor.begin(); itlist != lMotor.end(); itList++)
			std::cout << *itList << std::end*/

			/*list<Motor> motorList;
			motorList.push_back(mo1);
			motorList.push_back(mo2);
			//list<Motor> motorList;
			list<Motor>::iterator itlist;
			for (itlist = motorList.begin(); itlist != motorList.end(); it++) {
				cout << *itlist;
			}*/

			/*cout << "\n------STL LIST--------\n";
			list<Motor> lFloat;
			lFloat.push_back(mo1);
			lFloat.push_back(mo2);
			//lFloat.push_front(20.5f);
			list<Motor>::iterator itList;
			for (itList = lFloat.begin(); itList != lFloat.end(); itList++)
				cout << *itList << " ";
			list<float>::reverse_iterator rItList;
			cout << endl;
			for (rItList = lFloat.rbegin(); rItList != lFloat.rend(); rItList++)
				cout << *rItList << " ";*/

	list<Motor> motorList;
	Motor motor1;
	motorList.push_back(motor1);
	motorList.push_back(mo1);
	motorList.push_back(mo2);
	//motorList = { Motor(), Motor(), Motor() };
	list<Motor>::iterator itlist;
	int index = 0;
	for (/*list<Motor>::iterator it*/ itlist = motorList.begin(); itlist != motorList.end(); itlist++) {
		index++;
		cout << index << " . " << *itlist;
		cout << endl;
	}


	cout << "\n------STL SET--------\n";
	set<Masina> masinaset;
	masinaset.insert(m3);
	masinaset.insert(m2);


	set<Masina>::iterator itSet;
	for (itSet = masinaset.begin(); itSet != masinaset.end(); itSet++)
	{
		cout << *itSet << " ";
	}

	cout << "\n------STL MAP--------\n";
	map<int, Masina> masinaMap;
	masinaMap[0] = m3;
	masinaMap[1] = m2;

	map<int, Masina>::iterator itMap;
	for (itMap = masinaMap.begin(); itMap != masinaMap.end(); itMap++)
	{
		cout << endl << itMap->first << " " << itMap->second;
	}

	cout << endl;
	analyzer.stop_monitor_user_activity("Melisa");
	// generate activity report
	analyzer.generate_activity_report();

	return 0;
}