-- https://hasura.io/learn/database/postgresql/core-concepts/6-postgresql-relationships/ Pour la synthaxe des relations entre les différentes tables (à vérifier auprès de quelqu'un) A ENLEVER AVANT LE RENDU

DROP SCHEMA IF EXISTS programme_but CASCADE;

CREATE SCHEMA programme_but;

SET SCHEMA 'programme_but';

-- CRÉATION DES TABLES

CREATE TABLE _activites (
    lib_activite VARCHAR(50),
    competence VARCHAR(50) NOT NULL,
    CONSTRAINT lib_activite_pk PRIMARY KEY (lib_activite)
);

CREATE TABLE _competences (
    competence VARCHAR(50),
    CONSTRAINT competence_pk PRIMARY KEY (competence)
);


CREATE TABLE _niveau(
    numero_n INTEGER,
    CONSTRAINT numero_n_pk PRIMARY KEY (numero_n)
);

CREATE TABLE _semestre(
    numero_sem INTEGER,
    numero_n INTEGER NOT NULL,
    CONSTRAINT numero_sem_pk PRIMARY KEY (numero_sem)
);

CREATE TABLE _ue(
    code_ue VARCHAR(10),
    lib_activite VARCHAR(50) NOT NULL,
    numero_sem INTEGER NOT NULL,
    CONSTRAINT code_ue_pk PRIMARY KEY (code_ue)
);

CREATE TABLE _parcours(
    code_p CHAR,
    libelle_parcours VARCHAR(50) NOT NULL,
    nbre_gpe_td_p INTEGER NOT NULL,
    nbre_gpe_tp_p INTEGER NOT NULL,
    CONSTRAINT code_p_pk PRIMARY KEY (code_p)
);

CREATE TABLE _ressources(
    code_r VARCHAR(10),
    lib_r VARCHAR(50) NOT NULL,
    nb_h_cm_pn INTEGER NOT NULL,
    nb_h_td_pn INTEGER NOT NULL,
    nb_h_tp_pn INTEGER NOT NULL,
    numero_sem INTEGER NOT NULL,
    code_p CHAR NOT NULL,
    CONSTRAINT code_r_pk PRIMARY KEY (code_r)
);


CREATE TABLE _sae(
    code_SAE VARCHAR(10),
    lib_SAE VARCHAR(50) NOT NULL,
    nb_h_td_enc INTEGER NOT NULL,
    nb_h_td_projet_autonomie INTEGER NOT NULL,
    CONSTRAINT code_sae_pk PRIMARY KEY (code_sae)
);


ALTER TABLE _activites
    ADD CONSTRAINT activites_fk_competences
        FOREIGN KEY (competence) REFERENCES _competences(competence);


ALTER TABLE _ue
    ADD CONSTRAINT ue_fk_activites
        FOREIGN KEY (lib_activite) REFERENCES _activites(lib_activite);


ALTER TABLE _ressources
    ADD CONSTRAINT ressources_fk_semestre
        FOREIGN KEY (numero_sem) REFERENCES _semestre(numero_sem);


ALTER TABLE _ressources
    ADD CONSTRAINT ressources_fk_parcours
        FOREIGN KEY (code_p) REFERENCES _parcours(code_p);


ALTER TABLE _semestre
    ADD CONSTRAINT semestre_fk_niveau
        FOREIGN KEY (numero_n) REFERENCES _niveau(numero_n);

ALTER TABLE _ue
    ADD CONSTRAINT ue_fk_semestre
        FOREIGN KEY (numero_sem) REFERENCES _semestre(numero_sem);
-- AJOUT DE LA RELATION MANY-TO-MANY EN BAS À DROITE

CREATE TABLE _comprend_r(
    code_r VARCHAR(10) NOT NULL,
    code_sae VARCHAR(10) NOT NULL,
    nb_h_td_c INTEGER NOT NULL,
    nb_h_tp_c INTEGER NOT NULL,
    PRIMARY KEY (code_r, code_sae)
);

ALTER TABLE _comprend_r
    ADD CONSTRAINT fk_ressources FOREIGN KEY(code_r) REFERENCES _ressources(code_r);

ALTER TABLE _comprend_r
    ADD CONSTRAINT fk_sae FOREIGN KEY(code_sae) REFERENCES _sae(code_sae);

-- AJOUT DE LA RELATION TERNAIRE

CREATE TABLE _correspond(
    lib_activite VARCHAR(50),   
    numero_n INTEGER,
    code_p CHAR(10),
    PRIMARY KEY (lib_activite, numero_n, code_p)
);

ALTER TABLE _correspond
    ADD CONSTRAINT fk_activites FOREIGN KEY(lib_activite) REFERENCES _activites(lib_activite);

ALTER TABLE _correspond
    ADD CONSTRAINT fk_niveau FOREIGN KEY(numero_n) REFERENCES _niveau(numero_n);

ALTER TABLE _correspond
    ADD CONSTRAINT fk_parcours FOREIGN KEY(code_p) REFERENCES _parcours(code_p);


-- PENSER À VÉRIFIER LE TOUT
