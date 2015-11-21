using UnityEngine;
using System.Collections;

public class States : MonoBehaviour {


	/*// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
        
	}*/

    public enum CharacterStates { NORMAL, BURNING, WET }

    float changeState(CharacterStates state){
        switch (state){
            case CharacterStates.NORMAL:
                return 100;
            case CharacterStates.BURNING:
                //Llamada a iniciar contador de muerte;
                return 0;
            case CharacterStates.WET:
                return 50;
            default:
                return 100;
        }
    }
}
