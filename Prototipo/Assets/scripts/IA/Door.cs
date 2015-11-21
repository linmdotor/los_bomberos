using UnityEngine;
using System.Collections;
[RequireComponent(typeof(Life))]
[RequireComponent(typeof(BoxCollider))]
[RequireComponent(typeof(AudioSource))]
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
        //aud.PlayOneShot(aud.clip);
        GameObject aux = new GameObject();
        AudioSource asource = aux.AddComponent<AudioSource>();
        aux = Instantiate(aux);
        aux.GetComponent<AudioSource>().PlayOneShot(aud.clip);
        Destroy(aux, 3.0f);
        gameObject.active = false;
    }

}
