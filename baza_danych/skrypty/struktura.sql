USE ask_20;
SET character_set_client = utf8mb4 ;
CREATE TABLE question(
	`id` int primary key auto_increment,
    `pytanie` varchar(200)
)ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_cirelacje;
CREATE TABLE words (
	`id` int primary key auto_increment,
    `slowo` varchar(40)
)ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_cirelacje;
CREATE TABLE `relacje` (
  `id_question` int(11) NOT NULL,
  `id_words` int(11) NOT NULL,
  `stan` tinyint(4) DEFAULT NULL,
  KEY `id_question` (`id_question`),
  KEY `id_words` (`id_words`),
  CONSTRAINT `relacje_ibfk_1` FOREIGN KEY (`id_question`) REFERENCES `question` (`id`),
  CONSTRAINT `relacje_ibfk_2` FOREIGN KEY (`id_words`) REFERENCES `words` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;