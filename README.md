# AMTslayyerr
Gra 3D w stylu boomer-shooter.  
Celem gry jest pokonywanie przeciwników AMT (Ant Mutated Titans), którzy z niewyjaśnionych powodów pojawili się w mieście.   
Rogrywka trwa do śmierci gracza, który musi walczyć z niekończącymi się falami przeciwników.  
Sterowanie jest intuicyjne (poruszanie -> wsad, lewy przycisk myszy-> strzał)  
![image](https://github.com/SZOlafo/AMTslayyerr/assets/105805460/f3060243-5954-4618-a618-d8ec90a06bb2)
(Graphic generated by chat GPT)  
Wylistowanie wątków:  
AntGruntThread -> wątek odpowiada za logikę przeciwnika (porsuzanie się, podążanie za graczem, atakowanie, śmierć i respawn)  
shootingThread -> sprawdza czy przeciwnik został trafiny, jeśli tak zadaje obrażenia  
Main -> Wątek główny w programie z GLFW3 tworzy okno, inicjalizuje kontekst OpenGL i wchodzi w główną pętlę. W tej pętli pobiera wejście od użytkownika, aktualizuje stan aplikacji oraz rysuje scenę. Po każdym cyklu pętli wymienia bufory, co aktualizuje wyświetlany obraz. Pętla trwa, dopóki użytkownik nie zamknie okna(wciśnięcie f na klawiaturze).  
Sekcje krytyczne:  
Poruszanie przeciwników-> muteks przy funkcji poruszania się przeciwników i gracza. Tylko 1 encja zmienia swoje położenie w danym momencie, aby możliwe było wykrywanie kolizji.  
Detekcja strzałów-> flaga zdarzeń która zapewnia że każdy z przeciwników przetwarz logikę sprawdzenia trafienia i zadania obrażeń raz dla każdego strzału  
Pobieranie inputu od użytkownika realizowane jest przez bibliotekę GLFW  
