#!/usr/bin/php

<?php

const DEF_DOX = '* \def';
const BRIEF_DOX = '* \brief';
const PARAM_DOX = '* \param';
const RETURN_DOX = '* \return';
const FN_DOX = '* \fn';
const FILE_DOX = '* \file';
const AUTHOR_DOX = '* \author';
const DATE_DOX = '* \date';
const VERSION_DOX = '* \version';

function initDoc($fileName) {

   $ConstanteCode = "";

   $FileCode = "";

   $FonctionListCode = "";

   $FonctionCode = "";

   $AuthorCode = "";

   $DateCode = "";

   $VersionCode = "";

   $lines = file($fileName);
   foreach ($lines as $key => $value) {
      if (strcmp($value, "") !== 0) {
         if (testDef($value)) {
            $pointeur = 1;
   
            $pos = strpos($value, DEF_DOX)+strlen(DEF_DOX);
            $codeLine = '<p class="code constantes">' . substr($value, $pos) . '</p>';

            while (strpos($lines[$key+$pointeur], "*")) {
               if (testBrief($lines[$key+$pointeur])) {
                  $pos = strpos($lines[$key+$pointeur], BRIEF_DOX)+strlen(BRIEF_DOX);
                  $codeLine = $codeLine
                            . '<p class="code">' . substr($lines[$key+$pointeur], $pos) . '</p>';

               }
               $pointeur++;
            }
            $ConstanteCode = $ConstanteCode
            . $codeLine;
         }
   
         if (testFn($value)) {
            $param = 0;
            $pointeur = 1;
            $pos = strpos($value, FN_DOX)+strlen(FN_DOX);
            $codeLine = '<h3>' . substr($value, $pos) . '</h3>';
            $FonctionListCode = $FonctionListCode
                           . $codeLine;
   
   
            while (strpos($lines[$key+$pointeur], "*") != false) {
               if (testBrief($lines[$key+$pointeur])) {
                  $pos = strpos($lines[$key+$pointeur], BRIEF_DOX)+strlen(BRIEF_DOX);
                  $codeLine = $codeLine
                            . '<p class="code">' . substr($lines[$key+$pointeur], $pos) . '</p>';

               }
               if (testParam($lines[$key+$pointeur])) {
                $pos = strpos($lines[$key+$pointeur], PARAM_DOX)+strlen(PARAM_DOX);
                if ($param == 0) {
                   $codeLine = $codeLine
                             . '<h4>Variables :</h4>'; 
                }
                $codeLine = $codeLine
                          . '<p class="code">' . substr($lines[$key+$pointeur], $pos) . '</p>';
                $param++;

             }
               if (testReturn($lines[$key+$pointeur])) {
                  $pos = strpos($lines[$key+$pointeur], RETURN_DOX)+strlen(RETURN_DOX);
                  $codeLine = $codeLine
                            . '<h4>Renvoie :</h4>'
                            . '<p class="code">' . substr($lines[$key+$pointeur], $pos) . '</p>';
               }
               $pointeur++;
            }
            $FonctionCode = $FonctionCode . '<article class="f">'
            . $codeLine . '</article>';
         }
   
         if (testAuthor($value)) {
            $pos = strpos($value, AUTHOR_DOX)+strlen(AUTHOR_DOX);
            $codeLine = substr($value, $pos);
            $AuthorCode = $AuthorCode
                           . $codeLine;
         }
   
         if (testDate($value)) {
            $pos = strpos($value, DATE_DOX)+strlen(DATE_DOX);
            $codeLine = substr($value, $pos);
            $DateCode = $DateCode
                           . $codeLine;
         }
   
         if (testVersion($value)) {
            $pos = strpos($value, VERSION_DOX)+strlen(VERSION_DOX);
            $codeLine = substr($value, $pos);
            $VersionCode = $VersionCode
                           . $codeLine;
         }

         if (testFile($value)) {
            $pointeur = 1;
            $pos = strpos($value, FILE_DOX)+strlen(FILE_DOX);
            $codeLine = "<h1> Fichier : " . substr($value, $pos) . "</h1>";


            while (strpos($lines[$key+$pointeur], "*") != false ) {
               if (testBrief($lines[$key+$pointeur])) {
                  $pos = strpos($lines[$key+$pointeur], BRIEF_DOX)+strlen(BRIEF_DOX);
                  $codeLine = $codeLine
                              . '<p class="code">' . substr($lines[$key+$pointeur], $pos) . '</p>';
               }
               $pointeur++;
            }
            $FileCode = $FileCode
            . $codeLine;
      }
      }
      }

      $htmlCode = '<!DOCTYPE html>' . "\n"
      . '<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="fr" lang="fr">' . "\n"
      . '<head>' . "\n"
      . '<meta charset="utf-8" />' . "\n"
      . '<title>Doxygen</title>' . "\n"
      . '<link rel="stylesheet" href="styletech.css" >' . "\n"
      . '</head>' . "\n"
      . '<body>' . "\n"
      . '<header>' . "\n"
      . $FileCode . "\n"
      . '</header>' . "\n"
      . '<article class="const">' . "\n"
      . '<h2>Déclaration des constantes : </h2>' . "\n"
      . $ConstanteCode . "\n"
      . '</article>' . "\n"
      . '<div>' . "\n"
      . '<article class="def">' . "\n"
      . '<h2>Liste des fonctions : </h2>' . "\n"
      . $FonctionListCode . "\n"
      . '</article>' . "\n"
      . '<section>' . "\n"
      . $FonctionCode . "\n"
      . '</section>' . "\n"
      . '</div>' . "\n"
      . '<footer>' . "\n"
      . '<p>Description d un code source C en HTML</p>' . "\n"
      . '<p> Auteur : ' . $AuthorCode . '</p>'  . "\n"
      . '<p> Date de Création : ' . $DateCode . '</p>' . "\n"
      . '<p> Version : ' . $VersionCode . '</p>' . "\n"
      . '</footer>' . "\n"
      . '</body>';
   
   return $htmlCode . "\n";
}

function testDef($line) {
   $resultat = false;
   if (strpos($line, DEF_DOX)) {
      $resultat = true;
   }
   return $resultat;
}

function testBrief($line) {
   $resultat = false;
   if (strpos($line, BRIEF_DOX)) {
      $resultat = true;
   }
   return $resultat;
}

function testParam($line) {
   $resultat = false;
   if (strpos($line, PARAM_DOX)) {
      $resultat = true;
   }
   return $resultat;
}

function testReturn($line) {
   $resultat = false;
   if (strpos($line, RETURN_DOX)) {
      $resultat = true;
   }
   return $resultat;
}

function testFn($line) {
   $resultat = false;
   if (strpos($line, FN_DOX)) {
      $resultat = true;
   }
   return $resultat;
}

function testFile($line) {
   $resultat = false;
   if (strpos($line, FILE_DOX)) {
      $resultat = true;
   }
   return $resultat;
}

function testAuthor($line) {
   $resultat = false;
   if (strpos($line, AUTHOR_DOX)) {
      $resultat = true;
   }
   return $resultat;
}

function testDate($line) {
   $resultat = false;
   if (strpos($line, DATE_DOX)) {
      $resultat = true;
   }
   return $resultat;
}

function testVersion($line) {
   $resultat = false;
   if (strpos($line, VERSION_DOX)) {
      $resultat = true;
   }
   return $resultat;
}


function version($option) {
   $fileText = "";

   $result = "";
   $config = file("config");
   foreach ($config as $key => $lines) {
      if (strpos($lines, "VERSION=") !== false) {
         $pos = strpos($lines, "VERSION=")+strlen("VERSION=");
         $configValue = substr($lines, $pos);
         $num = explode('.',$configValue);
         switch ($option) {
            case '--major':
               $num[2] = '0';
               $num[1] = '0';
               $num[0]++;
               break;
            case '--minor':
               $num[2] = '0';
               $num[1]++;
               break;
            case '--build':
               $num[2]++;
               break;
            default:
               echo "Erreur d'option";
               break;
         }
         $result = $result . $num[0] . "." . $num[1] . "." . $num[2];
         $lines = "VERSION=" . $result;
      }
      $fileText = $fileText . $lines;
   }

   unlink("config");
   $fConfig = fopen("config", 'w');
   fwrite($fConfig, $fileText);
   fclose($fConfig);

   return $result;
}
$version = version($argv[1]);
$f = fopen("doc-tech-".$version.".html", "w");
fwrite($f, initDoc('src1.c'));
fclose($f);
?>