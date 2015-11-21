using UnityEngine;
using System.Collections;
[RequireComponent(typeof(Life))]
[RequireComponent(typeof(BoxCollider))]
public class Door : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    public void OnDead()
    {
        gameObject.active = false;
    }
}
