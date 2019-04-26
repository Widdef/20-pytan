--Zapytanie do decydowania jakie pytanie zadać po pierwszej odpowiedzi dla bazy z 5 słów
SELECT relacje.id_question, COUNT(relacje.id_question) AS wystapienia, liczba.ilosc FROM 
(
	SELECT * FROM relacje WHERE (id_words = 2 OR id_words = 3 OR id_words = 5) AND (id_question != 2) 
) AS relacje, 
(
	SELECT id_question, COUNT(id_question) AS ilosc FROM (
        SELECT * FROM relacje WHERE (id_words = 2 OR id_words = 3 OR id_words = 5) AND (id_question != 2) 
    ) AS relacje WHERE stan = 1 GROUP BY id_question
) AS liczba 
WHERE relacje.id_question = liczba.id_question GROUP BY id_question ORDER BY wystapienia DESC

--ograniczona tabela relacje 
SELECT * FROM 
(
    SELECT * FROM relacje WHERE (id_words = 2 OR id_words = 3 OR id_words = 5) AND (id_question != 2) 
) AS relacje

--policzenie pozytywnych odpowiedzi dla ograniczonej tabeli relacje
SELECT id_question, COUNT(id_question) AS ilosc FROM 
    (
        SELECT * FROM relacje WHERE id_words = 2 OR id_words = 3 OR id_words = 5 
    ) AS relacje 
        WHERE stan = 1 GROUP BY id_question
