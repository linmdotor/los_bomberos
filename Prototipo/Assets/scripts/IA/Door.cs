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
        //sonido de la puerta al romperse
        AudioSource aud = gameObject.GetComponent<AudioSource>();
        aud.PlayOneShot(aud.clip);

        gameObject.active = false;
    }
}
