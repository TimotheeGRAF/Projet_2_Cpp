<!DOCTYPE html>
<html>
	<head>
		<meta charset="utf-8" />
		<title>Page de test</title>
		<link rel="stylesheet" type="text/css" href="style.css">
	</head>
	<body>
	<?php 
		include("connexion.php");
		if(isset($_POST['rechercher'])){
		$requete = "SELECT No_chanson, Nom_chanson, Annee_de_creation, Nom_interprete, Nom_album
					FROM chanson c, album a, interprete i
					WHERE c.No_interprete = i.No_interprete
					AND c.No_album = a.No_album";
			if ($_POST['titre'] == NULL) {
				// titre de chanson vide donc pas d'ajout à la requête
			}
			else {
				$requete .= " AND Nom_chanson LIKE '%".$_POST['titre']."%'";
			}
			if ($_POST['chanteur'] == NULL) {
				// chanteur vide donc pas d'ajout à la requête
			}
			else {
				$requete .= " AND Nom_interprete LIKE '%".$_POST['chanteur']."%'";
			}
			if ($_POST['album'] == NULL) {
				// album vide donc pas d'ajout à la requête
			}
			else {
				$requete .= " AND Nom_album LIKE '%".$_POST['album']."%'";
			}
			if ($_POST['date'] == NULL && $_POST['date2'] == NULL) {
				// date vide donc pas d'ajout à la requête
			}
			elseif($_POST['date'] == NULL && $_POST['date2'] != NULL) {
				$requete .= " AND annee_de_creation < ".$_POST['date2'];
			}
			elseif($_POST['date'] != NULL && $_POST['date2'] == NULL) {
				$requete .= " AND annee_de_creation > ".$_POST['date'];
			}
			else { // les 2 champs dates sont remplis
				$requete .= " AND annee_de_creation BETWEEN ".$_POST['date']." AND ".$_POST['date2'];
			}
			if ($_POST['tri'] == NULL) {
				// pas de tri
			}
			else {
				$requete .= " ORDER BY ".$_POST['tri']." ASC";
			}
			
			echo "<table>
					<tr><th>Num chanson</th><th>Nom chanson</th><th>Année de création</th><th>Nom interprète</th><th>Nom album</th></tr>";
					$recherche = $bdd->query($requete);
					while($donnees = $recherche->fetch()) {
						echo "<tr>
								<td>".$donnees['No_chanson']."</td>
								<td>".$donnees['Nom_chanson']."</td>
								<td>".$donnees['Annee_de_creation']."</td>
								<td>".$donnees['Nom_interprete']."</td>
								<td>".$donnees['Nom_album']."</td>";
					}
			
		}
		else {
	?>
	<h1>Recherche</h1>
	<form method="post" action="recherche.php">
		<p>
			<label for="titre">Titre : </label><input type="text" name="titre" id="titre" /><br />
			<label for="chanteur">Chanteur : </label><input type="text" name="chanteur" id="chanteur" /><br />
			<label for="album">Album : </label><input type="text" name="album" id="album" /><br />
			<label for="date">Année : </label><input type="text" name="date" id="date" placeholder="De..." /> - <input type="text" name="date2" id="date2" placeholder="À..." /><br />
			<label for="tri">Trier par : </label>
			<select name="tri" id="tri">
				<option value="nom_chanson">Titre de chanson</option>
				<option value="annee_de_creation">Année de création</option>
				<option value="nom_interprete">Interprète</option>
				<option value="nom_album">Titre de l'album</option>
			</select>
			<br />
			<input type="submit" name="rechercher" value="Rechercher" />
		</p>
	</form>
	<?php
		}
	?>
	</body>
</html>