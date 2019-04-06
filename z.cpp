// z.cpp
//
// LZW fa építő C++ átizata a C valtozatbol
// Programozó Páternoszter
//
// Copyright (C) 2011, Bátfai Norbert, nbatfai@inf.unideb.hu, nbatfai@gmail.com
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// Ez a program szabad szoftver; terjeszthetõ illetve módosítható a
// Free Software Foundation által kiadott GNU General Public License
// dokumentumában leírtak; akár a licenc 3-as, akár (tetszõleges) késõbbi
// változata szerint.
//
// Ez a program abban a reményben kerül közreadásra, hogy hasznos lesz,
// de minden egyéb GARANCIA NÉLKÜL, az ELADHATÓSÁGRA vagy VALAMELY CÉLRA
// VALÓ ALKALMAZHATÓSÁGRA való származtatott garanciát is beleértve.
// További részleteket a GNU General Public License tartalmaz.
//
// A felhasználónak a programmal együtt meg kell kapnia a GNU General
// Public License egy példányát; ha mégsem kapta meg, akkor
// tekintse meg a <http://www.gnu.org/licenses/> oldalon.
//
//
// Version history:
//
// 0.0.1, http://progpater.blog.hu/2011/02/19/gyonyor_a_tomor
// 0.0.2, csomópontok mutatóinak NULLázása (nem fejtette meg senki :)
// 0.0.3, http://progpater.blog.hu/2011/03/05/labormeres_otthon_avagy_hogyan_dolgozok_fel_egy_pedat
// 0.0.4, a C verzióból svn: bevezetes/C/ziv/z.c átírjuk C++-ra
//        http://progpater.blog.hu/2011/03/31/imadni_fogjatok_a_c_t_egy_emberkent_tiszta_szivbol
//

#include <iostream>

class LZWBinFa
{
public:
    LZWBinFa (char b = '/'):betu (b), balNulla (NULL), jobbEgy (NULL) {};
    ~LZWBinFa () {};
    LZWBinFa *nullasGyermek () {
        return balNulla;
    }
    LZWBinFa *egyesGyermek ()
    {
        return jobbEgy;
    }
    void ujNullasGyermek (LZWBinFa * gy)
    {
        balNulla = gy;
    }
    void ujEgyesGyermek (LZWBinFa * gy)
    {
        jobbEgy = gy;
    }
    void kiir (void)
    {
        melyseg = 0;
        kiir (this);
    }
    void szabadit (void)
    {
        szabadit (jobbEgy);
        szabadit (balNulla);
    }


private:
    char betu;
    LZWBinFa *balNulla;
    LZWBinFa *jobbEgy;

    LZWBinFa (const LZWBinFa &);
    LZWBinFa & operator=(const LZWBinFa &);

    int melyseg;

    void kiir (LZWBinFa * elem)
    {
        if (elem != NULL)
        {
            ++melyseg;
            kiir (elem->jobbEgy);
            // ez a postorder bejáráshoz képest
            // 1-el nagyobb mélység, ezért -1
            for (int i = 0; i < melyseg; ++i)
                std::cout << "---";
            std::cout << elem->betu << "(" << melyseg - 1 << ")" << std::endl;
            kiir (elem->balNulla);
            --melyseg;
        }
    }
    void szabadit (LZWBinFa * elem)
    {
        if (elem != NULL)
        {
            szabadit (elem->jobbEgy);
            szabadit (elem->balNulla);
            delete elem;
        }
    }

};

int
main ()
{
    char b;
    LZWBinFa gyoker, *fa = &gyoker;
    
    while (std::cin >> b)
    {
        if (b == '0')
        {
            // van '0'-s gyermeke az aktuális csomópontnak?
            if (!fa->nullasGyermek ()) // ha nincs, csinálunk
            {
                LZWBinFa *uj = new LZWBinFa ('0');
                fa->ujNullasGyermek (uj);
                fa = &gyoker;
            }
            else // ha van, arra lépünk
            {
                fa = fa->nullasGyermek ();
            }
        }
        else
        {
            if (!fa->egyesGyermek ())
            {
                LZWBinFa *uj = new LZWBinFa ('1');
                fa->ujEgyesGyermek (uj);
                fa = &gyoker;
            }
            else
            {
                fa = fa->egyesGyermek ();
            }
        }
    }

    gyoker.kiir ();
    gyoker.szabadit ();

    return 0;
}
