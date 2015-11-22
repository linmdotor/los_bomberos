using UnityEngine;
using System.Collections;

[RequireComponent(typeof(AudioSource))]
public class DelayedSound : MonoBehaviour {

    public float delay = 10;
    public bool repeatAlways = true;

	// Use this for initialization
	void Start () {
        StartCoroutine(PlaySoundAfterDelay(gameObject.GetComponent<AudioSource>(), delay));
	}

    /*
     * Play the sound waiting a delay. Repeat again if "repeatAlways" is true
     */
    IEnumerator PlaySoundAfterDelay(AudioSource audioSource, float delay)
    {
        if (audioSource == null)
            yield break;
        do {
            yield return new WaitForSeconds(delay);
            audioSource.Play();

        } while (repeatAlways);
        
    }
}
