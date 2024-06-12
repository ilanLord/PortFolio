z#!/usr/bin/php

<?php
echo  "Nom du fichier ? ";
$fichier = readline();
$lignes = file($fichier);
$html = '';
$dansBlock = false;
$dansTableau = false;
$colonneTab = [];
$liste = [];
$cpt = 0;
$dansliste = false;


$html .= "
<!DOCTYPE html>
<html lang='fr'>
    <head>
        <meta charset='UTF-8'>
        <meta name='viewport' content='width=device-width, initial-scale=1.0'>
        <link rel='stylesheet' href='styleuser.css'>
        <title>DOC_UTILISATEUR</title>
    </head>
    <body>\n";
foreach ($lignes as $ligne) {
    if (strpos($ligne, "###### ") !== false) {
        // Titre
        $rest = substr($ligne,  strlen("###### "));
        $rest = str_replace(array("\n"), array(''), $rest);
        $html .= "        <h6>$rest</h6>\n";
    } 
    elseif (strpos($ligne, "#####") !== false) {
        // Titre
        $rest = substr($ligne,  strlen("##### "));
        $rest = str_replace(array("\n"), array(''), $rest);
        $html .= "        <h5>$rest</h5>\n";
    } 
    elseif (strpos($ligne, "####") !== false) {
        // Titre
        $rest = substr($ligne,  strlen("#### "));
        $rest = str_replace(array("\n"), array(''), $rest);
        $html .= "        <h4>$rest</h4> \n";
    } 
    elseif (strpos($ligne, "###") !== false) {
        // Titre
        $rest = substr($ligne,  strlen("### "));
        $rest = str_replace(array("\n"), array(''), $rest);
        $html .= "        <h3>$rest</h3>\n";
    } 
    elseif (strpos($ligne, "##") !== false) {
        // Titre
        $rest = substr($ligne,  strlen("## "));
        $rest = str_replace(array("\n"), array(''), $rest);
        $html .= "        <h2>$rest</h2>\n        <hr>\n";
    } 
    elseif (strpos($ligne, "#") !== false) {
        // Titre
        $rest = substr($ligne,  strlen("# "));
        $rest = str_replace(array("\n"), array(''), $rest);
        $html .= "        <h1>$rest</h1>\n        <hr>\n";
    }
     elseif (strpos($ligne, "```") !== false) {
        // Blocs de code
        $dansBlock = !$dansBlock;
        if ($dansBlock) {
            $html .= "        <blockquote>\n<code>\n    <pre>\n";
        } 
        else {
            $html .= "</pre>\n</code>\n        </blockquote>\n";
        }
    } 
    elseif (preg_match('/\[(.*?)\]\((.*?)\)/', $ligne, $l)) {
        // Liens vidéo
        $text = $l[1];
        $url = $l[2];
        $html .= "        <a href=\"$url\">$text</a>\n";
    } 
    elseif (strpos($ligne, "- [ ] ") !== false) {
        // Checkbox
        $rest = substr($ligne, strlen("- [ ] "));
        $rest = str_replace(array("\n"), array(''), $rest);
        $html .= "        <div>\n";
        $html .= "            <input type=\"checkbox\"/>\n";
        $html .= "            <label>$rest</label>\n";
        $html .= "        </div>\n";
    } 
    elseif ( strpos($ligne, "- [x] ") !== false){
        // Checkbox avec croix
    	$rest = substr($ligne, strlen("- [ ] "));
        $rest = str_replace(array("\n"), array(''), $rest);
        $html .= "        <div>\n";
        $html .= "            <input type=\"checkbox\" checked/>\n";
        $html .= "            <label>$rest</label>\n";
        $html .= "        </div>\n";
    }
    elseif (strpos($ligne, '>') === 0) {
        // Lignes commençant par '>'
        $rest = substr($ligne, 1);
        $rest = str_replace(array("\n"), array(''), $rest);
        $html .= "        <blockquote>\n          $rest\n        </blockquote>\n";
    }
    elseif (strpos($ligne, "- ") !== false) {
        // Listes - / Sous-liste
        $rest = substr($ligne, strlen("- "));
        $rest = str_replace(array("\n"), array(''), $rest);
        if (strpos($rest, "- ") === 0) {
            $sous_liste[] = substr($rest, strlen("- "));
        } 
        else {
            if (!empty($sous_liste)) {
                $html .= "            <ul>\n";
                foreach ($sous_liste as $contenu_liste) {
                    $html .= "               <li>$contenu_liste</li>\n";
                }
                $html .= "            </ul>\n";
                $html .= "        </ul>\n";
                $sous_liste = [];
            }
            $liste[] = $rest;
       }
    }
    elseif (strpos($ligne, '|') !== false) {
        // Tableau
    	if (!$dansTableau) {
            $dansTableau = true;
            $colonneTab = [];
        }

        $cellules = explode('|', $ligne);
        $l_ligne = [];
        foreach ($cellules as $cellule) {
            if (!empty($cellule)) {
                $cellule = trim($cellule);
                $l_ligne[] = $cellule;
            }
        }
        $colonneTab[] = $l_ligne;
    } 
    elseif ($dansTableau) {
        $dansTableau = false;
        $html .= "        <table>\n";
        foreach ($colonneTab as $l_ligne) {
            if ($cpt == 0){
                $html .= "            <thead>\n";
            }
            $html .= "                <tr>\n";
            foreach ($l_ligne as $cellule) {
            	if ($cpt < 3){
                    
                    if($cellule != ""){
                        $html .= "                   <th>$cellule</th>\n";
                        $cpt += 1;
                        
                    } 
                }
                else{
                    if($cellule != ""){
                        $html .= "                    <td>$cellule</td>\n";
                    }
                }
            
            }
            $html .= "                </tr>\n";
            if ($cpt == 3){
                $html .= "            </thead>\n            <tbody>\n";
                $cpt++;
            }
        }
        $html .= "            </tbody>\n";
        $html .= "        </table>\n";
    }
    
    
    
    
    else {
        // Gras , italique
        $ligne = str_replace(array("\n"), array(''), $ligne);
        $ligne = preg_replace('/\*\*(.*?)\*\*/', '<strong>$1</strong>', $ligne);
        $ligne = preg_replace('/\*(.*?)\*/', '<em>$1</em>', $ligne);
        $ligne = preg_replace('/\`(.*?)\`/', '<em>$1</em>', $ligne);
        if ($ligne !== "" && !$dansBlock){
            $html .= "        <p>$ligne</p>\n";
        }
        if($dansBlock && strpos($ligne, "}") !== false){
            $html .= "        $ligne";
        }
        elseif($dansBlock){
            $html .= "        $ligne\n";
        }
        
        
    }
    if (!empty($liste)) {
        // Liste
        if ($dansliste == false){
            $html .= "        <ul>\n";
        }
        $dansliste = true;
        foreach ($liste as $i) {
            if (str_contains($i,"---") == false){
                $html .= "            <li>$i</li>\n";
                
            }
        }
        $liste = [];
 } 
}
$html .= "    </body>\n";
$html .= "</html>\n";

$f = fopen("doc-user-0.0.0.html","w");
fwrite($f, $html);
fclose($f);

?>