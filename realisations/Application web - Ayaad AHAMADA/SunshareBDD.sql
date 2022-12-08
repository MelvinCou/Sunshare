-- phpMyAdmin SQL Dump
-- version 5.0.4deb2
-- https://www.phpmyadmin.net/
--
-- Hôte : localhost:3306
-- Généré le : mar. 24 mai 2022 à 10:38
-- Version du serveur :  10.5.15-MariaDB-0+deb11u1
-- Version de PHP : 7.4.28

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données : `SunshareBDD`
--

-- --------------------------------------------------------

--
-- Structure de la table `Energies`
--

CREATE TABLE `Energies` (
  `id` int(11) NOT NULL,
  `id_utilisateur` int(11) DEFAULT NULL,
  `date` datetime NOT NULL DEFAULT current_timestamp(),
  `energie_produite` float NOT NULL,
  `energie_soutiree` float NOT NULL,
  `energie_injectee` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Déchargement des données de la table `Energies`
--

INSERT INTO `Energies` (`id`, `id_utilisateur`, `date`, `energie_produite`, `energie_soutiree`, `energie_injectee`) VALUES
(26, NULL, '2022-03-22 11:56:40', 50, 100, 20),
(27, NULL, '2022-03-22 12:11:00', 20, 121, 220),
(28, NULL, '2022-03-22 12:11:16', 20, 121, 220),
(31, NULL, '2022-03-25 09:28:35', 30.2, 20.2, 21.2),
(32, NULL, '2022-03-25 09:29:02', 30.2, 1.2, 21.2),
(40, NULL, '2022-03-22 11:54:00', 255, 258, 147),
(41, NULL, '2022-03-21 11:50:59', 2550, 2581, 1479),
(42, NULL, '2022-03-22 09:50:59', 20, 21, 79);

-- --------------------------------------------------------

--
-- Structure de la table `Energies_Annuelle`
--

CREATE TABLE `Energies_Annuelle` (
  `id_Energies_Annuelle` int(11) NOT NULL,
  `date` year(4) NOT NULL,
  `energie_produite` int(5) NOT NULL DEFAULT 0,
  `energie_soutiree` int(5) NOT NULL DEFAULT 0,
  `energie_injectee` int(5) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Déchargement des données de la table `Energies_Annuelle`
--

INSERT INTO `Energies_Annuelle` (`id_Energies_Annuelle`, `date`, `energie_produite`, `energie_soutiree`, `energie_injectee`) VALUES
(34, 2019, 0, 685, 0),
(35, 2019, 0, 689, 0),
(36, 2019, 0, 691, 0),
(37, 2019, 0, 692, 0),
(39, 2019, 0, 693, 0),
(40, 2019, 0, 693, 0),
(41, 2019, 63, 69, 18),
(42, 2020, 2, 3, 4),
(43, 2022, 7, 7, 7),
(45, 2019, 51, 125, 16),
(46, 2019, 44, 173, 14),
(47, 2019, 38, 214, 12),
(48, 2019, 34, 249, 11),
(49, 2019, 30, 278, 10),
(50, 2019, 25, 32, 7),
(51, 2022, 0, 0, 0),
(52, 2022, 0, 0, 0),
(53, 2019, 2, 458, 9),
(54, 2019, 18, 93, 8),
(55, 2019, 17, 128, 14),
(56, 2019, 16, 159, 20),
(57, 2019, 18, 187, 24),
(58, 2018, 27, 224, 33),
(59, 2019, 33, 239, 38);

-- --------------------------------------------------------

--
-- Structure de la table `Energies_Hebdomadaire`
--

CREATE TABLE `Energies_Hebdomadaire` (
  `id_Energies_Hebdomadaire` int(11) NOT NULL,
  `date` date NOT NULL,
  `energie_produite` int(5) NOT NULL DEFAULT 0,
  `energie_soutiree` int(5) NOT NULL DEFAULT 0,
  `energie_injectee` int(5) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Déchargement des données de la table `Energies_Hebdomadaire`
--

INSERT INTO `Energies_Hebdomadaire` (`id_Energies_Hebdomadaire`, `date`, `energie_produite`, `energie_soutiree`, `energie_injectee`) VALUES
(20, '2019-08-06', 0, 693, 0),
(21, '2019-08-06', 0, 694, 0),
(26, '2019-08-06', 8, 233, 7),
(27, '2019-08-06', 6, 348, 6),
(29, '2019-08-05', 4, 462, 4),
(30, '2019-08-09', 4, 490, 3),
(31, '2019-08-09', 3, 510, 3),
(32, '2022-05-01', 10, 9, 1),
(33, '2022-05-07', 21, 10, 11),
(34, '2022-05-14', 12, 5, 7),
(35, '2022-05-21', 20, 10, 10),
(36, '2022-05-28', 14, 7, 7),
(37, '2022-06-04', 9, 4, 3),
(38, '2019-08-27', 5, 50, 26),
(39, '2022-03-23', 0, 0, 0),
(40, '2022-03-23', 0, 0, 0),
(41, '2019-08-27', 0, 0, 0),
(42, '2019-08-27', 4, 118, 47),
(43, '2019-08-27', 3, 511, 194),
(44, '2019-08-27', 2, 516, 193),
(45, '2019-08-27', 140, 531, 204),
(46, '2019-08-20', 155, 404, 175),
(47, '2019-08-20', 187, 408, 189),
(48, '2019-08-27', 211, 411, 199);

-- --------------------------------------------------------

--
-- Structure de la table `Energies_Journaliere`
--

CREATE TABLE `Energies_Journaliere` (
  `id_Energies_Journaliere` int(11) NOT NULL,
  `date` date NOT NULL,
  `energie_produite` int(5) NOT NULL DEFAULT 0,
  `energie_soutiree` int(5) NOT NULL DEFAULT 0,
  `energie_injectee` int(5) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Déchargement des données de la table `Energies_Journaliere`
--

INSERT INTO `Energies_Journaliere` (`id_Energies_Journaliere`, `date`, `energie_produite`, `energie_soutiree`, `energie_injectee`) VALUES
(49, '2019-08-06', 0, 691, 0),
(50, '2019-08-05', 0, 691, 0),
(52, '2019-08-09', 0, 655, 0),
(53, '2019-08-09', 0, 655, 0),
(71, '2019-08-27', 0, 540, 190),
(72, '2019-08-27', 0, 540, 190),
(73, '2019-08-27', 419, 512, 232),
(74, '2022-05-12', 5, 3, 2),
(75, '2019-08-26', 350, 427, 260),
(76, '2019-08-26', 350, 427, 260),
(77, '2019-08-27', 350, 427, 260);

-- --------------------------------------------------------

--
-- Structure de la table `Energies_Mensuelle`
--

CREATE TABLE `Energies_Mensuelle` (
  `id_Energies_Mensuelle` int(11) NOT NULL,
  `date` date NOT NULL,
  `energie_produite` int(5) NOT NULL DEFAULT 0,
  `energie_soutiree` int(5) NOT NULL DEFAULT 0,
  `energie_injectee` int(5) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Déchargement des données de la table `Energies_Mensuelle`
--

INSERT INTO `Energies_Mensuelle` (`id_Energies_Mensuelle`, `date`, `energie_produite`, `energie_soutiree`, `energie_injectee`) VALUES
(45, '2022-04-07', 165, 10, 20),
(57, '2022-05-07', 6, 4, 3),
(58, '2022-06-07', 8, 4, 4),
(59, '2022-07-07', 10, 9, 1),
(60, '2022-08-07', 3, 2, 1),
(61, '2022-09-07', 12, 5, 7),
(63, '2022-10-07', 9, 4, 5),
(64, '2022-11-07', 10, 5, 5),
(65, '2019-08-00', 4, 242, 18),
(66, '2022-03-00', 0, 0, 0),
(67, '2022-03-00', 0, 0, 0),
(68, '2019-08-00', 0, 673, 0),
(69, '2019-08-00', 3, 248, 36),
(70, '2019-08-00', 2, 592, 97),
(71, '2019-08-00', 1, 586, 107),
(72, '2019-08-00', 60, 612, 87),
(73, '2019-07-27', 86, 524, 97),
(74, '2019-07-27', 112, 514, 113),
(75, '2019-08-27', 134, 506, 127);

-- --------------------------------------------------------

--
-- Structure de la table `Energies_TempsReel`
--

CREATE TABLE `Energies_TempsReel` (
  `id_Energies_TempsReel` int(11) NOT NULL,
  `date` datetime NOT NULL,
  `energie_produite` int(5) NOT NULL DEFAULT 0,
  `energie_soutiree` int(5) NOT NULL DEFAULT 0,
  `energie_injectee` int(5) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Déchargement des données de la table `Energies_TempsReel`
--

INSERT INTO `Energies_TempsReel` (`id_Energies_TempsReel`, `date`, `energie_produite`, `energie_soutiree`, `energie_injectee`) VALUES
(33, '2019-08-05 13:51:53', 250, 744, 0),
(34, '2019-08-05 13:52:03', 345, 700, 0),
(35, '2019-08-05 13:52:12', 154, 680, 0),
(36, '2019-08-05 13:52:23', 675, 660, 0),
(37, '2019-08-05 13:52:32', 102, 640, 0),
(38, '2019-08-05 14:00:58', 675, 797, 0),
(39, '2019-08-05 14:01:10', 914, 764, 0),
(40, '2019-08-05 14:01:19', 320, 731, 0),
(41, '2019-08-05 14:01:28', 645, 702, 0),
(42, '2019-08-05 14:01:39', 842, 681, 0),
(43, '2019-08-05 14:01:49', 425, 661, 0),
(44, '2019-08-05 14:01:58', 563, 634, 0),
(45, '2019-08-05 15:38:37', 245, 690, 0),
(46, '2019-08-05 15:38:57', 241, 688, 0),
(47, '2019-08-05 15:39:16', 352, 688, 0),
(48, '2019-08-05 15:39:27', 452, 655, 0),
(49, '2019-08-05 15:39:36', 124, 635, 0),
(50, '2019-08-05 15:39:46', 652, 688, 0),
(51, '2019-08-05 15:58:07', 352, 702, 0),
(52, '2019-08-05 15:58:28', 210, 700, 0),
(53, '2019-08-05 16:00:44', 752, 699, 0),
(54, '2019-08-05 16:00:55', 120, 753, 0),
(55, '2019-08-05 16:01:05', 354, 752, 0),
(56, '2019-08-05 16:01:14', 542, 669, 0),
(57, '2019-08-05 16:01:25', 245, 634, 0),
(58, '2019-08-05 16:01:35', 0, 762, 0),
(61, '2019-08-05 19:59:38', 0, 747, 0),
(62, '2019-08-05 20:01:02', 0, 758, 0),
(63, '2019-08-05 20:03:18', 0, 756, 0),
(64, '2019-08-05 20:07:51', 0, 761, 0),
(65, '2019-08-05 20:08:02', 0, 760, 0),
(66, '2019-08-05 20:15:47', 0, 757, 0),
(67, '2019-08-05 20:16:07', 0, 756, 0),
(68, '2019-08-05 20:16:17', 0, 758, 0),
(69, '2019-08-05 20:16:28', 0, 755, 0),
(72, '2019-08-05 21:15:22', 0, 0, 0),
(73, '2019-08-05 21:15:31', 0, 737, 0),
(74, '2019-08-05 21:15:41', 0, 664, 0),
(75, '2019-08-05 21:15:52', 0, 601, 0),
(76, '2019-08-05 21:17:38', 0, 830, 0),
(77, '2019-08-05 21:17:48', 0, 830, 0),
(78, '2019-08-05 21:17:59', 0, 791, 0),
(79, '2019-08-05 21:18:08', 0, 752, 0),
(80, '2019-08-05 21:18:18', 0, 708, 0),
(81, '2019-08-05 21:18:29', 0, 668, 0),
(82, '2019-08-05 21:18:38', 0, 670, 0),
(83, '2019-08-05 21:18:47', 0, 634, 0),
(84, '2019-08-05 21:18:59', 0, 584, 0),
(85, '2019-08-05 21:36:21', 0, 585, 0),
(86, '2019-08-05 21:36:32', 0, 686, 0),
(87, '2019-08-05 21:36:41', 0, 687, 0),
(88, '2019-08-05 21:36:51', 0, 719, 0),
(89, '2019-08-05 21:37:02', 0, 718, 0),
(90, '2019-08-09 20:36:16', 0, 722, 0),
(91, '2019-08-09 20:36:25', 0, 682, 0),
(92, '2019-08-09 20:36:35', 421, 631, 0),
(93, '2019-08-09 20:36:46', 356, 583, 0),
(96, '2019-08-19 14:53:50', 451, 808, 0),
(98, '2019-08-23 22:39:13', 452, 756, 0),
(99, '2019-08-23 22:39:34', 356, 759, 0),
(100, '2019-08-23 22:39:54', 102, 697, 0),
(101, '2019-08-26 13:50:43', 245, 792, 0),
(102, '2019-08-26 13:51:22', 752, 708, 0),
(103, '2019-08-26 13:54:01', 968, 715, 0),
(104, '2019-08-26 13:54:15', 426, 715, 0),
(105, '2019-08-26 13:56:52', 752, 715, 0),
(106, '2019-08-26 13:57:09', 352, 675, 0),
(107, '2019-08-26 13:59:48', 452, 0, 799),
(108, '2019-08-26 14:00:03', 245, 0, 724),
(110, '2019-08-26 20:50:40', 0, 796, 0),
(111, '2019-08-26 21:00:15', 0, 0, 796),
(112, '2022-05-13 16:21:30', 10, 5, 5),
(113, '2019-08-31 16:05:55', 0, 0, 799),
(114, '2022-05-20 15:38:07', 125, 90, 254),
(115, '2019-09-05 15:48:19', 0, 0, 785),
(116, '2019-09-05 15:48:34', 0, 0, 790),
(117, '2019-09-05 16:49:20', 0, 731, 0),
(118, '2019-09-05 16:49:33', 0, 748, 0);

--
-- Index pour les tables déchargées
--

--
-- Index pour la table `Energies`
--
ALTER TABLE `Energies`
  ADD PRIMARY KEY (`id`),
  ADD KEY `id_utilisateur` (`id_utilisateur`);

--
-- Index pour la table `Energies_Annuelle`
--
ALTER TABLE `Energies_Annuelle`
  ADD PRIMARY KEY (`id_Energies_Annuelle`);

--
-- Index pour la table `Energies_Hebdomadaire`
--
ALTER TABLE `Energies_Hebdomadaire`
  ADD PRIMARY KEY (`id_Energies_Hebdomadaire`);

--
-- Index pour la table `Energies_Journaliere`
--
ALTER TABLE `Energies_Journaliere`
  ADD PRIMARY KEY (`id_Energies_Journaliere`);

--
-- Index pour la table `Energies_Mensuelle`
--
ALTER TABLE `Energies_Mensuelle`
  ADD PRIMARY KEY (`id_Energies_Mensuelle`);

--
-- Index pour la table `Energies_TempsReel`
--
ALTER TABLE `Energies_TempsReel`
  ADD PRIMARY KEY (`id_Energies_TempsReel`);

--
-- AUTO_INCREMENT pour les tables déchargées
--

--
-- AUTO_INCREMENT pour la table `Energies`
--
ALTER TABLE `Energies`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=43;

--
-- AUTO_INCREMENT pour la table `Energies_Annuelle`
--
ALTER TABLE `Energies_Annuelle`
  MODIFY `id_Energies_Annuelle` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=60;

--
-- AUTO_INCREMENT pour la table `Energies_Hebdomadaire`
--
ALTER TABLE `Energies_Hebdomadaire`
  MODIFY `id_Energies_Hebdomadaire` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=49;

--
-- AUTO_INCREMENT pour la table `Energies_Journaliere`
--
ALTER TABLE `Energies_Journaliere`
  MODIFY `id_Energies_Journaliere` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=78;

--
-- AUTO_INCREMENT pour la table `Energies_Mensuelle`
--
ALTER TABLE `Energies_Mensuelle`
  MODIFY `id_Energies_Mensuelle` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=76;

--
-- AUTO_INCREMENT pour la table `Energies_TempsReel`
--
ALTER TABLE `Energies_TempsReel`
  MODIFY `id_Energies_TempsReel` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=119;

--
-- Contraintes pour les tables déchargées
--

--
-- Contraintes pour la table `Energies`
--
ALTER TABLE `Energies`
  ADD CONSTRAINT `Energies_ibfk_1` FOREIGN KEY (`id_utilisateur`) REFERENCES `utilisateurs` (`id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
