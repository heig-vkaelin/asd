//FORBIDDEN cout
//FORBIDDEN cerr
//FORBIDDEN printf
//FORBIDDEN puts
//FORBIDDEN putchar
//FORBIDDEN putc
#include "util.h"
#include "c.h"

int cnt = 0; // utilisez cette variable globale

void f0() noexcept {
	enter("f0");
// AJOUTEZ VOTRE CODE ICI ...

	static C c2 = C(++cnt);
	C c3 = C(++cnt);

// ... FIN DE VOTRE CODE
	leave("f0");
}

C *f1() {
	enter("f1");
	C *p;
// AJOUTEZ VOTRE CODE ICI ...

	p = new C(++cnt);

// ... FIN DE VOTRE CODE
	leave("f1");
	return p;
}

C *f2() {
	enter("f2");
	C *p;
// AJOUTEZ VOTRE CODE ICI ...

	p = new C[2]{++cnt, ++cnt};

// ... FIN DE VOTRE CODE
	leave("f2");
	return p;
}

void f3(C *p) noexcept {
	enter("f3");
// AJOUTEZ VOTRE CODE ICI ...

	new(p) C(++cnt);

// ... FIN DE VOTRE CODE
	leave("f3");
}

void f4(C *p, size_t n) noexcept {
	enter("f4");
// AJOUTEZ VOTRE CODE ICI ...

	for (C *ptr = p; ptr < p + n; ++ptr) {
		new(ptr) C{++cnt};
	}

// ... FIN DE VOTRE CODE
	leave("f4");
}

int main() {
	enter("main");
// AJOUTEZ VOTRE CODE ICI ...

	C c = C(++cnt);
	f0();
	f0();

	C *c5 = f1();
	C *c6c7 = f2();

	void *c8 = ::operator new(sizeof(C));
	f3((C *) c8);

	delete[] c6c7;
	delete c5;

	const size_t SIZE = 2;
	void *c9c10 = ::operator new(sizeof(C) * SIZE);
	f4((C *) c9c10, SIZE);

	delete (C *) c8;

	void *c11 = ::operator new(sizeof(C));
	f4((C *) c11, 1);

	for (auto *ptr = (C *) c9c10; ptr < (C *) c9c10 + SIZE; ++ptr) {
		ptr->~C();
	}
	::operator delete(c9c10);

	delete (C *) c11;

// ... FIN DE VOTRE CODE
	leave("main");
}
