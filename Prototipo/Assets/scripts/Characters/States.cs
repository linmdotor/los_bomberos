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

    public float m_wetDuration;
    private float m_currentTime;
    private CharacterStates currentState = CharacterStates.NORMAL;
    public float m_normalSpeed = 5;
    public float m_burningSpeed = 0;
    public float m_wetSpeed = 2;

    void Update()
    {
        m_currentTime -= Time.deltaTime;
        if (currentState == CharacterStates.WET && m_currentTime < 0.0f)
        {
            gameObject.SendMessage("normalState");
        }
    }

    public float changeState(CharacterStates state){
        currentState = state;
        switch (state){
            case CharacterStates.NORMAL:
                return m_normalSpeed;
            case CharacterStates.BURNING:
                //Llamada a iniciar contador de muerte;
                return m_burningSpeed;
            case CharacterStates.WET:
                return m_wetDuration;
            default:
                return 100;
        }
    }
    public CharacterStates getState()
    {
        return currentState;
    }
}
