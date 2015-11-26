using UnityEngine;
using System.Collections;
using System.Reflection;
using System;

public class PruebaReflexion : MonoBehaviour {

    [ExportableAttribute]
    public string type = "PruebaTipo";
    [ExportableAttribute]
    public int iPrueba = 0;
    [ExportableAttribute]
    public Vector3 vPrueba = new Vector3(1, 2, 3);
    

	// Use this for initialization
	void Start () {
        // Get the public methods.
        
	}
	
	// Update is called once per frame
	void Update () {
	
	}

}
