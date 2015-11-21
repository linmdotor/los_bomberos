using UnityEngine;
using System.Collections;

public class CameraFollows : MonoBehaviour
{
    public Transform Player;
    public Vector3 cameraOffset = new Vector3(0.0f, 3.0f, -2.0f);

    void LateUpdate()
    {
        if (Player != null)
            transform.position = Player.position + cameraOffset;
    }
}
