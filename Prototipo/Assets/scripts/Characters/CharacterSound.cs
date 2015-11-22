using UnityEngine;
using System.Collections;

[RequireComponent(typeof(AudioSource))]
public class CharacterSound : MonoBehaviour {

    private bool isActive = false;

    public void isMoving()
    {
        //if is not active, start the step sound loop
        if (!isActive)
        {
            isActive = true;
            AudioSource aud = gameObject.GetComponent<AudioSource>();
            aud.Play();

        }
    }

    public void isNotMoving()
    {
        //finish the step sound loop if is active
        if (isActive)
        {
            AudioSource aud = gameObject.GetComponent<AudioSource>();
            aud.Stop();
            isActive = false;
        }
    }
}
