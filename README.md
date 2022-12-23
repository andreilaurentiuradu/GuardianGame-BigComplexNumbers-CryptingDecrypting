# TEMA1-PCLP
312CC Radu Andrei-Laurențiu

Problema 1:
	Cerință: 
		Cine a câștigat jocul și ciclurile formate de 
		paznici prin deschiderea cutiilor
	
	Implementare:
		Pentru fiecare paznic, verificăm dacă ciclul format are 
		lungimea mai mică sau egală cu p / 2, unde p este numărul 
		de paznici. În cazul în care găsim un paznic care nu respectă 
		regulă înseamnă că paznicii pierd jocul. După ce am aflat dacă 
		paznicii au câștigat sau nu, parcurgem iar ciclurile formate 
		de cutii. Dacă prima cutie nu se află în niciun ciclu atunci 
		am descoperit un ciclu nou(nu se pot află simultan în 2 cicluri) 
		și îl afișăm Vectorul format de cutii este echivalentul unui 
		vector de "tați"
	
	Modularizarea codului:
		Am implementat următoarele funcțîi:
			testare_nr_cutii(întoarce o variabilă booleana ce reține 
			dacă am găsit un ciclu mai lung de p / 2)
			ciclu(verifică dacă am găsit un ciclu nou)
			main(funcția principala unde citim dateles și au loc 
			apelurile funcțiilor anterioare)
	Optimizare:
		Verificăm în funcția testare_nr_cutii dacă am trecut deja de 
		a (p / 2) -a cutie
	
	Durata implementării: 1h

Problema 2
	Cerință: 
		Funcționalitatea unui calculator pentru numere complexe ce 
		nu încap în tipuri de date primitive
	
	Implementare:
		Se stochează numerele în 2 tablouri unidimensionale(a, b). a 
		reține rezultatul operației anterioare(sau este primul număr), 
		iar b următorul număr cu care se va realiza o operație al cărei 
		rezultat va fi suprascris în tabloul a. Lucrăm pe prima jumătate 
		a tablourilor pentru partea reală. Dacă operația este o scădere 
		schimbăm semnul părțîi reale a lui b. Dacă părțile reale ale 
		celor două numere au același semn atunci facem adunarea lor, 
		în caz contrar facem scăderea numărului mai mic din numărul 
		mai mare(în modul) și păstrăm semnul numărului mai mare(în modul)
		Procedăm analog pentru cea imaginară. Rezultatul final va fi 
		reținut în tabloul a, pe care îl afișăm.
	
	Modularizarea codului:
		Am implementat următoarele funcțîi:
			compari(compară două numere întregi reținute în vectorii 
			de tip char, numere ce se află între două pozițîi din vectori)
			adunare_real(se realizează adunarea părților reale rezultat 
			stocat în a), analog adunare_imaginar
			scadere_real(se realizează scăderea părților reale rezultat 
			stocat în a), analog scadere_imaginar
			swap(interschimba 2 charuri)
			interschimbare(interschimba valorile ale doi vectori char 
			aflate între 2 pozițîi)
			schimbare_de_semn(schimbă semnul părților unui număr complex)
			faci_operatia(apelează funcțiile de adunare și scădere în 
			funcție de semnul părților)
			main(funcția principala unde citim datele, apelăm funcțiile 
			anterioare și afișăm rezultatul cerut, reținut în vectorul a)
	
	Durata implementării: 3-4h
	
Problema 3
	Cerință: Criptarea, respectiv decriptarea unui șir de caractere în 
	funcție de o cheie
	a) șir de caractere
	b) număr întreg
	
	Implementare: 
		a) Utilizăm o matrice inițializată cu spațîi în care punem șirul 
		de caractere(locurile rămase libere vor fi puse în șirul, 
		lungimea să putându-se modifică)
			-codificarea are loc în funcție de sortarea lexicografică a 
			cheii, interschimband coloanele matricei conform sorțarii
			-decodificarea are loc în funcție de modul în care trebuie 
			puse la loc caracterele caracterele conform sorțarii cheii
		b) Utilizăm un vector constant în care reținem literele din 
		alfabet(mari și mici) pentru a codifică mai ușor literele din șir
			-codificarea are loc copiind ultimele nr(numărul întreg ce 
			reprezintă cheia) caractere într-un șir auxiliar, 
			modificându-le conform tabloului în care reținem alfabetul 
			și a lui nr; concatenăm șirul s la șirul obținut(fără 
			ultimele nr) și copiem în s șirul ulterior obținut
			-decodificarea are loc modificând primele nr caractere 
			în funcție de tabloul în care reținem alfabetul și nr; 
			copiem în două șiruri auxiliare astfel; în primul primele 
			nr caractere iar în al doilea celelalte din s; copiem în s 
			caracterele din al doilea șir și concatenăm rezultatul cu 
			primul șir auxiliare
		Pentru toate rezultatul va fi întors tot în șirul inițial.
	
	Modularizarea codului
		Am implementat umratoarele funcțîi:
			litera_mare(verifică dacă caracterul este litera mare)
			litera_mica(verifică dacă caracterul este litera mică)
			codificareB(realizează codificarea de tip B)
			decodificareB(realizează decodificarea de tip B)
			swap_char(interschimba 2 variabile de tip char)
			swap_coloane(interschimba 2 coloane dintr-o matrice de 
			tip char)
			sortare(sortam coloanele matricei în funcție de cheie)
			creare_matriceA(creăm matricea pentru codificarea de tip A)
			codificareA(realizează codificarea de tip A apelând funcțiile 
			creare_matriceA și sortare)
			swap_int(interchimba 2 variabile de tip int)
			reverse_sort(află modul în care s-au interschimbat coloanele 
			conform codificariiA)
			creare_matrice_decod_A(creăm matricea șirului(nedecodificat))
			decodificareA(realizează decodificarea de tip A apelând 
			funcțiile creare_matrice_decod_A și reverse_sort)
			main(funcția principala în care are loc citirea datelor, și 
			apelul funcțiilor anterioare)

	Durata implementării: 30-32h

Problema 4 
	Cerință:
		a) numărul de mașini din fiecare tip(după combustibil)
		b) consumul total de combustibil și suma totală plătită pentru 
		numărul de km rulați de fiecare brand
		c) validarea numarelor de înmatriculare ale mașinilor

	Implementare:
		Se alocă dinamic memorie pentru tablourile brand, număr, 
		combustibil, consum și km.
		a) Folosim un vector de frecvența în care contorizăm numărul 
		de aparițîi al mașinilor din fiecare tip
		b) Reținem în 2 tablouri cantitatea de combustibil consumată 
		de fiecare mașînă și prețul acelei cantități. Marcăm într-un 
		vector boolean dacă poziția la care ne aflăm  în vector îi 
		corespunde unei mașini al cărei brand a mai fost până în acel
		moment. Reținem în acele pozițîi consumul total de combustibil 
		al brandului și suma total plătită
		c) Verificăm pentru fiecare mașînă în parte dacă numărul ei 
		corespunde tiparului unui număr de înmatriculare valid

	Modularizarea codului:
		Am implementat următoarele funcțîi:
			cerinta_unu(parcurge **combustibil și contorizează numărul 
			de mașini din fiecare tip)
			consum_per_masina(returnează consumul realizăm de o mașînă)
			grupez_branduri(marchează în vectorul boolean dacă poziția 
			la care ne aflăm în vector îi corespunde unei mașini al cărei 
			brand a mai fost până în acel moment; calculează și reține 
			consumul total și suma total pentru fiecare brand)
			cerinta_doi(reținem consumul și prețul combustibilului 
			fiecărei mașini și apelează funcția grupez_branduri)
			litera_mare(verifică dacă caracterul este litera mare)
			cifra(verifică dacă caracterul este cifra)
			numar_corect(verifică dacă un număr de înmatriculare se 
			află în tiparul unui număr valid)
			cerinta_trei(reține într-un vector boolean dacă numărul 
			fiecărei mașini este valid)
			main(funcția principala în care are loc citirea datelor, 
			apelul funcțiilor cerinta_unu, cerinta_doi, cerinta_trei 
			și în care se fac afișările)

	Optimizare:
		La cerință b) putem face alternativ verificarea dacă până în 
		acea poziție nu s-a găsit o mașînă dintr-un anumit brand și 
		calculul total al combustibilului și al prețului sau.
	
	Durata implementării: 2h
    	
