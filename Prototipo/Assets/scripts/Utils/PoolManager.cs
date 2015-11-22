using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class PoolManager {

	public GameObject 										goPool; //el objeto que contendra nuestra pool
	public int 												iPoolAmount; //numero de objetos que contendra la pool al iniciar

	private List<GameObject> 								lPoolList; //lista que mantiene los objetos


	// Use this for initialization
	public void Init () {
		lPoolList = new List<GameObject>(iPoolAmount);
		for ( int i = 0; i < iPoolAmount; i++ )
		{
			lPoolList.Add( GameObject.Instantiate(goPool) );
		}
	}

	public void Reset () {
		for ( int i = 0; i < iPoolAmount; i++ )
		{
			lPoolList[i].SetActive( false );
		}
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	/*
	 * Busca un item inactivo, si no lo encuentra lo crea y lo devuelve, bActive = true activa el GameObject
	 */
	public GameObject getObject(bool bActive)
	{
		bool bFind = false;
		int i = 0;
		GameObject goToReturn = null;
		while ( i < iPoolAmount && !bFind  )
		{
			if ( !lPoolList[i].activeInHierarchy )
			{
				bFind = true;
				goToReturn = lPoolList[i];
			}
			else
				i++;
		}
		if ( !bFind )
		{
			goToReturn = GameObject.Instantiate(goPool);
			lPoolList.Add( goToReturn );
			iPoolAmount++;
		}
		goToReturn.SetActive( bActive );
		return goToReturn;
	}

}
